/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "constants.h"

#include "calendar.h"
#include "clock.h"
#include "stopwatch.h"
#include "timer.h"

#define CLOCK_MODE       0
#define CALENDAR_MODE    1
#define STOPWATCH_MODE   2
#define TIMER_MODE       3
#define LASER_MODE       4
#define VOLTAGE_MODE     5
#define MODE_INTERVALS 171

/// Globals for holding the module structs.
Adafruit_SSD1306 display(OLED_RESET);
RTC_DS3231 rtc;

/// Miscellaneous state variables
short laserSquiggles = 0;
unsigned long currentTime;
unsigned long lastUpdateTime;
unsigned int deltaTime;

/// Button state trackers.
bool buttons[BUTTONS][STATES];

/// Updates the variables storing the state of the buttons and the ON_DOWN
/// state of the buttons.
void updateButtonStates() {
  byte buttonPins[BUTTONS] = { LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON };
  for (byte i = 0; i < BUTTONS; ++i) {
    buttons[i][STATE] = digitalRead(buttonPins[i]) == LOW;
    buttons[i][ON_DOWN] = buttons[i][STATE] &&
      (buttons[i][STATE] != buttons[i][LAST]);
    buttons[i][ON_UP] = !buttons[i][STATE] &&
      (buttons[i][STATE] != buttons[i][LAST]);
    if (buttons[i][STATE]) {
      buttons[i][HOLD] += deltaTime;
    } else if (!buttons[i][ON_UP]) {
      buttons[i][HOLD] = 0;
    }
    buttons[i][LAST] = buttons[i][STATE];
  }
}

/// Function called by Arduino to once at the start to initialize variables.
void setup() {
  Serial.begin(9600);

  pinMode(LEFT_BUTTON, INPUT);
  pinMode(MIDDLE_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.setTextColor(WHITE);
  display.clearDisplay();

  // Wait until the RTC is ready.
  while (!rtc.begin());
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lastUpdateTime = millis();
}

/// Function called by Arduino to update state.
void loop() {
  DateTime now = rtc.now();
  short potentiometer = analogRead(POTENTIOMETER);
  float batteryLevel = analogRead(BATTERY);
  float voltage = (batteryLevel / ANALOG_LIMIT) * VOLTAGE_MAX * 2;
  byte mode = potentiometer / MODE_INTERVALS;

  currentTime = millis();
  deltaTime = currentTime - lastUpdateTime;

  updateButtonStates();
  updateStopwatch();
  updateTimer();

  // All the modes are guaranteed to be mutually exclusive so their code will
  // never overlap.
  if (mode == CLOCK_MODE) {
    updateClockOnInput(buttons);
    displayClock(display, now);
  } else {
    turnOnClockScreen();
  }

  if (mode == CALENDAR_MODE) {
    displayCalendar(display);
  }

  if (mode == STOPWATCH_MODE) {
    updateStopwatchOnInput(buttons);
    displayStopwatch(display);
  }

  if (mode == TIMER_MODE) {
    updateTimerOnInput(buttons);
    displayTimer(display);
  }

  if (mode == LASER_MODE) {
    display.setTextSize(1);
    display.setCursor(0, 5);
    display.print(F("Laser"));
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.setCursor(20, 35);
    if (buttons[LEFT][STATE] ||
        buttons[MIDDLE][STATE] ||
        buttons[RIGHT][STATE]) {
      display.print(F("ON"));
      for (int i = 0; i < laserSquiggles; ++i) {
        display.print("~");
      }
      laserSquiggles = (laserSquiggles + 1) % 8;
      digitalWrite(LASER, HIGH);
    } else {
      display.print(F("OFF"));
      digitalWrite(LASER, LOW);
    }
  } else {
    digitalWrite(LASER, LOW);
  }

  if (mode == VOLTAGE_MODE) {
    display.setTextSize(1);
    display.setCursor(0, 5);
    display.print(F("Battery Voltage"));
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.print(voltage);
    display.println(F("V"));
  }

  display.display();
  display.clearDisplay();

  lastUpdateTime = currentTime;
}
