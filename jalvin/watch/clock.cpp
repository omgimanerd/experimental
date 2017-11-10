/// Module for displaying the clock.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "clock.h"

const char* DAY_NAME[] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Friday",
  "Saturday"
};

void displayAnalogClock(Adafruit_SSD1306 display, DateTime t) {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  int handLocations[3][2];
  float seconds_rad = t.second() * SECONDS_TO_RADIANS;
  float minutes_rad = t.minute() * MINUTES_TO_RADIANS;
  float hours_rad = t.hour() * HOURS_TO_RADIANS + minutes_rad / 12;

  // Second hand X
  handLocations[0][0] = CLOCK_X + cos(seconds_rad) * SECOND_HAND_LENGTH;
  // Second hand Y
  handLocations[0][1] = CLOCK_Y - sin(seconds_rad) * SECOND_HAND_LENGTH;
  // Minute hand X
  handLocations[1][0] = CLOCK_X + cos(minutes_rad) * MINUTE_HAND_LENGTH;
  // Minute hand Y
  handLocations[1][1] = CLOCK_Y - sin(minutes_rad) * MINUTE_HAND_LENGTH;
  // Hour hand X
  handLocations[2][0] = CLOCK_X + cos(hours_rad) * HOUR_HAND_LENGTH;
  // Hour hand Y
  handLocations[2][1] = CLOCK_Y - sin(hours_rad) * HOUR_HAND_LENGTH;

  // Draw the clock circle.
  display.drawCircle(CLOCK_X, CLOCK_Y, CLOCK_RADIUS, WHITE);
  display.fillCircle(CLOCK_X, CLOCK_Y, 1, WHITE);

  // Draw the ticks around the clock face.
  for (int i = 0; i < 12; i++) {
    float rad = i * HOURS_TO_RADIANS;
    display.drawPixel(CLOCK_X + cos(rad) * TICK_LENGTH,
                      CLOCK_Y - sin(rad) * TICK_LENGTH, WHITE);
  }
  // Draw the clock hands
  for (int i = 0; i < 3; ++i) {
    display.drawLine(
      CLOCK_X, CLOCK_Y, handLocations[i][0], handLocations[i][1], WHITE);
  }

  display.setCursor(64, 20);
  display.setTextColor(WHITE);
  display.println(DAY_NAME[(t.unixtime() / 86400) % 7]);

  display.setCursor(64, 30);
  display.print(t.month());
  display.print('/');
  display.print(t.day());
  display.print('/');
  display.println(t.year());

  display.setCursor(64, 40);

  display.print(t.hour());
  display.print(':');
  display.print(t.minute());
  display.print(':');
  display.println(t.second());
}

void displayDigitalClock(Adafruit_SSD1306 display, DateTime t) {
  display.setCursor(85, 50);
  int H = t.hour();
  bool am;
  int newH;
  if (H == 0) {
    am = true;
    newH = 12;
  } else if (H < 12) {
    am = true;
    newH = H;
  } else if (H == 12) {
    am = false;
    newH = H;
  } else if (H > 12) {
    am = false;
    newH = H - 12;
  }
  if (am == true) {
    display.print('A');
  }
  else if (am == false) {
    display.print('P');
  }
  display.print('M');
}
