/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "clock.h"
#include "stopwatch.h"

#define OLED_MOSI      9
#define OLED_CLK      10
#define OLED_DC       11
#define OLED_CS       12
#define OLED_RESET    13
#define LASER          2
#define LEFT_BUTTON    3
#define RIGHT_BUTTON   4
#define POTENTIOMETER A0
#define BATTERY       A1

#define POTENTIOMETER_LIMIT 1023
#define VOLTAGE_MAX 3.3

#define LASER_SETTING      400
#define STOPWATCH_SETTING  700
#define CLOCK_SETTING     1000

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RTC_DS3231 rtc;

bool powerSavingMode = false;

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

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextColor(WHITE);
  display.clearDisplay();

  while (!rtc.begin());
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  updateButtonStates();

  float potentiometer = analogRead(POTENTIOMETER);
  float batteryLevel = analogRead(BATTERY);

  float batteryVoltage = (batteryLevel / POTENTIOMETER_LIMIT) * VOLTAGE_MAX * 2;

  if (!powerSavingMode) {
    if (potentiometer > CLOCK_SETTING) {
      displayAnalogClock(display, now);
      if (leftButtonToggleState) {
        powerSavingMode = true;
      }
    } else if (potentiometer > STOPWATCH_SETTING) {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Stopwatch");
      if (leftButtonToggleState) {
        toggleStopwatch();
      }
      updateStopwatch();
      displayStopwatch(display);
    } else if (potentiometer > LASER_SETTING) {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Laser");

      display.setCursor(30, 30);
      display.setTextSize(2);
      display.print(leftButtonState ? "ON" : "OFF");
      digitalWrite(LASER, leftButtonState ? HIGH : LOW);
    } else {
      display.setTextSize(1);
      display.setCursor(0, 5);
      display.print("Battery Voltage");

      display.setCursor(30, 30);
      display.setTextSize(2);
      display.print(batteryVoltage);
      display.println("V");
    }
  } else if (leftButtonToggleState) {
    powerSavingMode = false;
  }
  display.display();
  display.clearDisplay();
}
