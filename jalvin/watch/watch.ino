/// Main watch driver code.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "constants.h"

// #include "calendar.h"
#include "clock.h"
// #include "stopwatch.h"

#define LASER          2
#define RIGHT_BUTTON   3
#define MIDDLE_BUTTON  5
#define LEFT_BUTTON    6
#define OLED_MOSI      9
#define OLED_CLK      10
#define OLED_DC       11
#define OLED_CS       12
#define OLED_RESET    13
#define POTENTIOMETER A0
#define BATTERY       A1

#define CLOCK_MODE     0
#define CALENDAR_MODE  1
#define STOPWATCH_MODE 2
#define LASER_MODE     3
#define VOLTAGE_MODE   4

/// Globals for holding the module structs.
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RTC_DS3231 rtc;

/// Holds the current potentiometer value.
short potentiometer = 0;

/// Miscellaneous state variables
bool screenOff = false;
short laserSquiggles = 0;
float batteryLevel, voltage;

/// Button state trackers.
bool buttonPins[3] = { LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON };
bool buttons[3][3];

/// Holds the potentiometer interval ranges for the watch modes.
int MODE_INTERVALS[5][2] = {
  { 0, 200 },
  { 201, 400 },
  { 401, 600 },
  { 601, 800 },
  { 801, 1024 }
};

/// Returns whether or not the watch is set in a certain mode.
bool isMode(short mode) {
  return MODE_INTERVALS[mode][0] <= potentiometer &&
    potentiometer <= MODE_INTERVALS[mode][1];
}

/// Updates the variables storing the state of the buttons and the toggle
/// state of the buttons.
void updateButtonStates() {
  for (byte i = 0; i < 3; ++i) {
    buttons[i][STATE] = digitalRead(buttonPins[i]) == LOW;
    buttons[i][TOGGLE] = buttons[i][STATE] &&
      (buttons[i][STATE] != buttons[i][LAST]);
    buttons[i][LAST] = buttons[i][STATE];
  }
}

void displayTitle(const char* title) {
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(title);
}

/// Function called by Arduino to once at the start to initialize variables.
void setup() {
  Serial.begin(9600);

  pinMode(LEFT_BUTTON, INPUT);
  pinMode(MIDDLE_BUTTON, INPUT);
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
  potentiometer = analogRead(POTENTIOMETER);
  batteryLevel = analogRead(BATTERY);
  voltage = (batteryLevel / ANALOG_LIMIT) * VOLTAGE_MAX * 2;

  updateButtonStates();
  // updateStopwatch();

  // All the modes are guaranteed to be mutually exclusive so their code will
  // never overlap.
  if (isMode(CLOCK_MODE)) {
    if (!screenOff) {
      displayAnalogClock(display, now);
    }
    screenOff = buttons[LEFT][TOGGLE] ? !screenOff : screenOff;
  }

  if (isMode(CALENDAR_MODE)) {
    // displayTitle("Calendar");
    // displayCalendar(display);
  }

  if (isMode(STOPWATCH_MODE)) {
    // if (leftButton[TOGGLE]) {
    //   toggleStopwatch();
    // } else if (rightButton[TOGGLE]) {
    //   resetStopwatch();
    // }
    // displayStopwatch(display);
  }

  if (isMode(LASER_MODE)) {
    displayTitle("Laser");
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.print(buttons[LEFT][STATE] ? "ON" : "OFF");
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

  if (isMode(VOLTAGE_MODE)) {
    displayTitle("Battery Voltage");
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.print(voltage);
    display.println("V");
  }

  Serial.println(potentiometer);

  display.display();
  display.clearDisplay();
}
