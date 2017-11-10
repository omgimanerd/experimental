/// Module for displaying the clock
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include "RTClib.h"

const char* DAY_NAME = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Friday",
  "Saturday"
};

int[][] calculateHandLocations(DateTime t) {

}

void drawAnalogClock(Adafruit_SSD1306 display, DateTime t) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  float second_y = CLOCK_Y - ((cos(t.second() * 0.1047)) * SECOND_HAND_LENGTH);
  float second_x = CLOCK_X + ((sin(t.second() * 0.1047)) * SECOND_HAND_LENGTH);
  float minute_y = CLOCK_Y - ((cos(t.minute() * 0.1047)) * MINUTE_HAND_LENGTH);
  float minute_x = CLOCK_X + ((sin(t.minute() * 0.1047)) * MINUTE_HAND_LENGTH);
  float hour_y = CLOCK_Y - ((cos((t.hour() * 0.5236) + (t.minute() * 0.0087))) * HOUR_HAND_LENGTH);
  float hour_x = CLOCK_X + ((sin((t.hour() * 0.5236) + (t.minute() * 0.0087))) * HOUR_HAND_LENGTH);
  for (int i = 0; i < 12; i++) {
    display.drawPixel(CLOCK_X + ((sin(i * 0.5236)) * (hour_length + 13)), CLOCK_Y - ((cos(i * 0.5236)) * (hour_length + 13)) ,WHITE);
  }

  display.drawCircle(CLOCK_X, CLOCK_Y, CLOCK_RADIUS, WHITE);
  display.fillCircle(CLOCK_X, CLOCK_Y, 1, WHITE);
  display.drawLine(CLOCK_X, CLOCK_Y, hour_x, hour_y, WHITE);
  display.drawLine(CLOCK_X, CLOCK_Y, minute_x, minute_y, WHITE);
  display.drawLine(CLOCK_X, CLOCK_Y, second_x, second_y, WHITE);
  display.setCursor(64, 20);
  display.setTextColor(WHITE);

  int day_of_week = (t.unixtime() / 86400) & 7;
  display.println(DAY_NAME[day_of_week]);

  display.setCursor(64, 30);
  display.print(t.month(), DEC);
  display.print('/');
  display.print(t.day(), DEC);
  display.print('/');
  display.println(t.year(), DEC);

  display.setCursor(64, 40);

  display.print(t.hour(), DEC);
  display.print(':');
  display.print(t.minute(), DEC);
  display.print(':');
  display.println(t.second(), DEC);
}


void drawDigitalClock(Adafruit_SSD1306 display, DateTime t) {
  display.setCursor(85, 50);
  int H = t.hour();
  bool am;
  int newH;
  if (H == 0) {
    am = true;
    newH = 12;
  }
  else if (H < 12) {
    am = true;
    newH = H;
  }
  else if (H == 12) {
    am = false;
    newH = H;
  }
  else if (H > 12) {
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
