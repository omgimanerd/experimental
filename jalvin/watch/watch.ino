/// Watch code

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
#define LEFT_BUTTON    4
#define RIGHT_BUTTON   3
#define POTENTIOMETER A0

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RTC_DS3231 rtc;

int potPin;
int batteryLevel;
float batteryVoltage;
bool powerSavingMode = false;
int numCards = 3;

bool leftButtonState;
bool leftButtonToggleState;
bool leftLastButtonState;
bool rightButtonState;
bool rightButtonToggleState;
bool rightLastButtonState;

void updateButtonStates() {
  leftButtonState = digitalRead(LEFT_BUTTON) == LOW;
  leftButtonToggleState = leftButtonState &&
    (leftButtonState != leftLastButtonState);
  leftLastButtonState = rightButtonState;
  rightButtonState = digitalRead(RIGHT_BUTTON) == LOW;
  rightButtonToggleState = rightButtonState &&
    (rightButtonState != rightLastButtonState);
  rightLastButtonState = rightButtonState;
}

void setup() {
  pinMode(topButton, INPUT);
  pinMode(bottomButton, INPUT);

  digitalWrite(topButton, HIGH);
  digitalWrite(bottomButton, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC);

  while (!rtc.begin());

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  updateButtonStates();
  DateTime now = rtc.now();
  potPin = analogRead(A0);
  batteryLevel = analogRead(A6);
  batteryVoltage = batteryLevel * (3.3 / 1023.0) * 2;

  if (!powerSavingMode) {
    if (potPin < 100) {
      displayAnalogClock(display, now);
      if (buttonToggleState) {
        powerSavingMode = true;
      }
    }
    else if (potPin < 400) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,5);
      display.print("Stopwatch");
      if (buttonToggleState) {
        toggleStopwatch();
      }
      updateStopwatch();
      displayStopwatch(display);
    }
    else {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,5);
      display.print("Battery Voltage");
      display.setCursor(0, 30);
      display.setTextSize(2);
      display.print(batteryVoltage);
      display.println("V");
      display.display();
    }
  }
  else if (buttonToggleState) {
    powerSavingMode = false;
  }
  display.display();
  display.clearDisplay();
}
