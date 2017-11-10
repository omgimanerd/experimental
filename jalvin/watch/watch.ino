/// Watch code

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "clock.h"
#include "stopwatch.h"

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
#define BUTTON1     4
#define BUTTON2     3

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RTC_DS3231 rtc;

const int topButton = 4;
const int bottomButton = 3;

int potPin;
int batteryLevel;
float batteryVoltage;
boolean powerSavingMode = false;
int numCards = 3;

bool buttonState;
bool buttonToggleState;
bool lastButtonState;

void updateButtonTracking() {
  buttonState = digitalRead(topButton) == LOW;
  buttonToggleState = buttonState && (buttonState != lastButtonState);
  lastButtonState = buttonState;
}

bool otherbuttonState;
bool otherbuttonToggleState;
bool otherlastButtonState;

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

  while (!rtc.begin());

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  updateButtonTracking();
  otherupdateButtonTracking();
  DateTime now = rtc.now();
  potPin = analogRead(A0);
  batteryLevel = analogRead(A6);
  batteryVoltage = batteryLevel * (3.3 / 1023.0) * 2;

  if (!powerSavingMode) {
    if (potPin < 100) {
      displayAnalogClock(display, rtc.now());
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
