/// Module for bluetooth communication.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

#include "constants.h"

#include "calendar.h"

static unsigned long lastCalendarUpdate = 0;

/// Updates the calendar if necessary.
void updateCalendar() {
  unsigned long currentTime = millis();
  if (currentTime - lastCalendarUpdate > POLLING_INTERVAL_MS) {
    // do update
  }
  lastCalendarUpdate = currentTime;
}

void displayCalendar(Adafruit_SSD1306 display) {
  display.setCursor(TITLE_TEXT_X, TITLE_TEXT_Y);
  display.print(F("Calendar"));
}
