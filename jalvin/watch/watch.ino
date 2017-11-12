/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "clock.h"
#include "stopwatch.h"

#define LASER                  2
#define RIGHT_BUTTON           3
#define LEFT_BUTTON            4
#define OLED_MOSI              9
#define OLED_CLK              10
#define OLED_DC               11
#define OLED_CS               12
#define OLED_RESET            13
#define POTENTIOMETER         A0
#define BATTERY               A1

#define ANALOG_LIMIT        1023
#define VOLTAGE_MAX          3.3

#define CLOCK_MODE             0
#define STOPWATCH_MODE         1
#define LASER_MODE             2
#define VOLTAGE_MODE           3

/// Globals for holding the module structs.
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RTC_DS3231 rtc;

/// Holds the potentiometer interval ranges for the watch modes.
int MODE_INTERVALS[4][2] = {
  { 0, 300 },
  { 301, 600 },
  { 601, 900 },
  { 901, 1024 }
};

/// Returns whether or not the watch is set in a certain mode.
bool isMode(short potentiometer, short mode) {
  return MODE_INTERVALS[mode][0] <= potentiometer &&
    potentiometer <= MODE_INTERVALS[mode][1];
}

/// Button state trackers [STATE, TOGGLE, LAST]
bool leftButton[3];
bool rightButton[3];

/// Updates the variables storing the state of the buttons and the toggle
/// state of the buttons.
void updateButtonStates() {
  leftButton[0] = digitalRead(LEFT_BUTTON) == LOW;
  leftButton[1] = leftButton[0] && (leftButton[0] != leftButton[2]);
  leftButton[2] = leftButton[0];
  leftButton[0] = digitalRead(RIGHT_BUTTON) == LOW;
  leftButton[1] = leftButton[0] && (leftButton[0] != rightButton[2]);
  rightButton[2] = leftButton[0];
}

/// Miscellaneous state variables
bool screenOff = false;
short laserSquiggles = 0;

/// Function called by Arduino to once at the start to initialize variables.
void setup() {
  Serial.begin(9600);
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC);
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

  updateButtonStates();
  updateStopwatch();

  if (!screenOff) {
    // All the modes are guaranteed to be mutually exclusive so the display code
    // will never overlap.
    if (isMode(potentiometer, CLOCK_MODE)) {
      Serial.print("CLOCK ");
      displayAnalogClock(display, now);
      if (leftButton[1]) {
        screenOff = true;
      }
    }

    if (isMode(potentiometer, STOPWATCH_MODE)) {
      Serial.print("STOPWATCH ");
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Stopwatch");
      if (leftButton[1]) {
        toggleStopwatch();
      }
      displayStopwatch(display);
    }

    if (isMode(potentiometer, LASER_MODE)) {
      Serial.print("LASER ");
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Laser");
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.print(leftButton[0] ? "ON" : "OFF");
      display.setCursor(25, 35);
      if (leftButton[0]) {
        for (int i = 0; i < laserSquiggles; ++i) {
          display.print("~");
        }
        laserSquiggles = (laserSquiggles + 1) % 8;
      }
      digitalWrite(LASER, leftButton[0] ? HIGH : LOW);
    } else {
      digitalWrite(LASER, LOW);
    }

    if (isMode(potentiometer, VOLTAGE_MODE)) {
      Serial.print("VOLTAGE ");
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Battery Voltage");
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.print(voltage);
      display.println("V");
    }
  } else if (leftButton[1]) {
    screenOff = false;
  }

  Serial.println(potentiometer);

  display.display();
  display.clearDisplay();
}
