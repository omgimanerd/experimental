/// Watch code

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "RTClib.h"

#include "clock.h"
#include "imu.h"
#include "stopwatch.h"

RTC_DS3231 rtc;

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int topButton = 4;
const int bottomButton = 3;

int potPin;
int batteryLevel;
float batteryVoltage;
boolean powerSavingMode = false;
int numCards = 3;

boolean buttonState;
boolean buttonToggleState;
boolean lastButtonState;

void updateButtonTracking() {
  buttonState = digitalRead(topButton) == LOW;
  buttonToggleState = buttonState && (buttonState != lastButtonState);
  lastButtonState = buttonState;
}

boolean otherbuttonState;
boolean otherbuttonToggleState;
boolean otherlastButtonState;

void otherupdateButtonTracking() {
  otherbuttonState = digitalRead(bottomButton) == LOW;
  otherbuttonToggleState = otherbuttonState && (otherbuttonState != otherlastButtonState);
  otherlastButtonState = otherbuttonState;
}

void setup()   {
  Serial.begin(9600);

  pinMode(topButton, INPUT);
  pinMode(bottomButton, INPUT);

  digitalWrite(topButton, HIGH);
  digitalWrite(bottomButton, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC);

  if (! rtc.begin()) {
    while (1);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!lsm.begin())
  {
    while (1);
  }
}

void loop() {
  updateButtonTracking();
  otherupdateButtonTracking();
  DateTime now = rtc.now();
  potPin = analogRead(A0);
  batteryLevel = analogRead(A6);
  batteryVoltage = batteryLevel * (3.3 / 1023.0) * 2;
  lsm.read();

  if (!powerSavingMode) {
    if (potPin < 100) {
      displayClock(rtc.now());
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
        updateStopWatchState();
      }
      updateStopWatch();
      displayStopWatch();
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
