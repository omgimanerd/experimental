/// Module for displaying the clock.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTCZero.h>

#include "buttons.h"
#include "constants.h"

#include "clock.h"

const char DAY_NAMES[7][10] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

/// Given the display struct and the current DateTime struct, this function
/// draws an analog clock and displays other relevant time information on the
/// face of the display.
void displayClock(Adafruit_SSD1306 display, RTCZero rtc) {
  // Some basic math for drawing the clock hands.
  short handLocations[2][2];
  short h = rtc.getHours();
  short m = rtc.getMinutes();
  float minutes_rad = m * (TAU / 60.0);
  float hours_rad = (h * (TAU / 12.0)) + (minutes_rad / 12.0);

  // Minute hand X
  handLocations[0][0] = CLOCK_X + sin(minutes_rad) * MINUTE_HAND_LENGTH;
  // Minute hand Y
  handLocations[0][1] = CLOCK_Y - cos(minutes_rad) * MINUTE_HAND_LENGTH;
  // Hour hand X
  handLocations[1][0] = CLOCK_X + sin(hours_rad) * HOUR_HAND_LENGTH;
  // Hour hand Y
  handLocations[1][1] = CLOCK_Y - cos(hours_rad) * HOUR_HAND_LENGTH;

  // Draw the clock circle.
  display.drawCircle(CLOCK_X, CLOCK_Y, CLOCK_RADIUS, WHITE);
  display.fillCircle(CLOCK_X, CLOCK_Y, 1, WHITE);

  // Draw the ticks around the clock face.
  for (short i = 0; i < 12; i++) {
    float rad = i * (TAU / 12);
    short x1 = CLOCK_X + sin(rad) * (CLOCK_RADIUS - TICK_DISTANCE);
    short y1 = CLOCK_Y - cos(rad) * (CLOCK_RADIUS - TICK_DISTANCE);
    short x2 = CLOCK_X + sin(rad) *
      (CLOCK_RADIUS - TICK_DISTANCE - TICK_LENGTH);
    short y2 = CLOCK_Y - cos(rad) *
      (CLOCK_RADIUS - TICK_DISTANCE - TICK_LENGTH);
    display.drawLine(x1, y1, x2, y2, WHITE);
  }

  // Draw the clock hands
  for (short i = 0; i < 2; ++i) {
    display.drawLine(
      CLOCK_X, CLOCK_Y, handLocations[i][0], handLocations[i][1], WHITE);
  }

  // Display the day of the week.
  char dateBuffer[DATE_BUFFER_SIZE];
  display.setCursor(DAY_OF_WEEK_X, DAY_OF_WEEK_Y);
  display.setTextColor(WHITE);
  int dayOfWeek = ((rtc.getEpoch() / 86400) + 4) % 7;
  strcpy_P(dateBuffer, DAY_NAMES[dayOfWeek]);
  display.println(dateBuffer);

  // Display the date.
  sprintf(dateBuffer,
    "%02d/%02d/%04d", rtc.getMonth(), rtc.getDay(), rtc.getYear() + 2000);
  display.setCursor(DATE_X, DATE_Y);
  display.print(dateBuffer);

  // Display the time.
  char timeBuffer[TIME_BUFFER_SIZE];
  if (h >= 13 && h <= 24) {
    h -= 12;
  }
  sprintf(timeBuffer, "%02d:%02d", h ? h : 12, m);
  display.setTextSize(2);
  display.setCursor(TIME_X, TIME_Y);
  display.print(timeBuffer);
  display.setTextSize(1);
}
