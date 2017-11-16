/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "constants.h"

#include "calendar.h"
#include "clock.h"
#include "stopwatch.h"
#include "timer.h"

#define LASER            2
#define LEFT_BUTTON      3
#define RIGHT_BUTTON     5
#define OLED_RESET       4
#define MIDDLE_BUTTON    6
#define POTENTIOMETER   A0
#define BATTERY         A1

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

/// Button state trackers.
bool buttons[3][3];

/// Updates the variables storing the state of the buttons and the toggle
/// state of the buttons.
void updateButtonStates() {
  byte buttonPins[3] = { LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON };
  for (byte i = 0; i < 3; ++i) {
    buttons[i][STATE] = digitalRead(buttonPins[i]) == LOW;
    buttons[i][TOGGLE] = buttons[i][STATE] &&
      (buttons[i][STATE] != buttons[i][LAST]);
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
}

/// Function called by Arduino to update state.
void loop() {
  DateTime now = rtc.now();
  short potentiometer = analogRead(POTENTIOMETER);
  float batteryLevel = analogRead(BATTERY);
  float voltage = (batteryLevel / ANALOG_LIMIT) * VOLTAGE_MAX * 2;
  byte mode = potentiometer / MODE_INTERVALS;

  updateButtonStates();
  updateStopwatch();
  updateTimer();

  // All the modes are guaranteed to be mutually exclusive so their code will
  // never overlap.
  if (mode == CLOCK_MODE) {
    updateClockOnInput(buttons);
    displayClock(display, now);
  }

  if (mode == CALENDAR_MODE) {
    display.setTextSize(1);
    display.setCursor(0, 5);
    display.print(F("Calendar"));
    // displayCalendar(display);
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
    display.print(buttons[LEFT][STATE] ? F("ON") : F("OFF"));
    display.setCursor(25, 35);
    if (buttons[LEFT][STATE]) {
      for (int i = 0; i < laserSquiggles; ++i) {
        display.print("~");
      }
      laserSquiggles = (laserSquiggles + 1) % 8;
    }
    digitalWrite(LASER, buttons[LEFT][STATE] ? HIGH : LOW);
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
}
