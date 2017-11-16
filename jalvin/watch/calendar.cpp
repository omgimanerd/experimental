/// Module for bluetooth communication.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

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
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(F("Calendar"));
}
