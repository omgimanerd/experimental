/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "clock.h"
#include "imu.h"
#include "stopwatch.h"

#define OLED_MOSI              9
#define OLED_CLK              10
#define OLED_DC               11
#define OLED_CS               12
#define OLED_RESET            13
#define LASER                  2
#define LEFT_BUTTON            3
#define RIGHT_BUTTON           4
#define POTENTIOMETER         A0
#define BATTERY               A1

#define POTENTIOMETER_LIMIT 1023
#define VOLTAGE_MAX          3.3

#define CLOCK_SETTING       1000
#define STOPWATCH_SETTING    750
#define LASER_SETTING        500
#define IMU_SETTING          250

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
RTC_DS3231 rtc;

bool screenOff = false;
int laserSquiggles = 0;

bool leftButtonState;
bool leftButtonToggleState;
bool leftLastButtonState;
bool rightButtonState;
bool rightButtonToggleState;
bool rightLastButtonState;

/// Updates the variables storing the state of the buttons and the toggle
/// state of the buttons.
void updateButtonStates() {
  leftButtonState = digitalRead(LEFT_BUTTON) == LOW;
  leftButtonToggleState = leftButtonState &&
    (leftButtonState != leftLastButtonState);
  leftLastButtonState = leftButtonState;
  rightButtonState = digitalRead(RIGHT_BUTTON) == LOW;
  rightButtonToggleState = rightButtonState &&
    (rightButtonState != rightLastButtonState);
  rightLastButtonState = rightButtonState;
}

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

  // Wait until the LSM sensor is ready.
  // while (!lsm.begin());
}

/// Function called by Arduino to update state.
void loop() {
  DateTime now = rtc.now();
  updateButtonStates();
  updateStopwatch();

  float potentiometer = analogRead(POTENTIOMETER);
  float batteryLevel = analogRead(BATTERY);

  float batteryVoltage = (batteryLevel / POTENTIOMETER_LIMIT) * VOLTAGE_MAX * 2;

  if (potentiometer <= IMU_SETTING && potentiometer < LASER_SETTING) {
    digitalWrite(LASER, LOW);
  }

  display.clearDisplay();
  if (!screenOff) {
    if (potentiometer > CLOCK_SETTING) {
      displayAnalogClock(display, now);
      if (leftButtonToggleState) {
        screenOff = true;
      }
    } else if (potentiometer > STOPWATCH_SETTING) {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Stopwatch");
      if (leftButtonToggleState) {
        toggleStopwatch();
      }
      displayStopwatch(display);
    } else if (potentiometer > LASER_SETTING) {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Laser");
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.print(leftButtonState ? "ON" : "OFF");
      display.setCursor(25, 35);
      if (leftButtonState) {
        for (int i = 0; i < laserSquiggles; ++i) {
          display.print("~");
        }
        laserSquiggles = (laserSquiggles + 1) % 8;
      }
      digitalWrite(LASER, leftButtonState ? HIGH : LOW);
    } else if (potentiometer > IMU_SETTING) {
      // displayIMU(display, lsm);
    } else {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Battery Voltage");
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.print(batteryVoltage);
      display.println("V");
    }
  } else if (leftButtonToggleState) {
    screenOff = false;
  }
  display.display();
}
