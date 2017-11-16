/// Module for bluetooth communication.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

#include "calendar.h"

static unsigned long lastCalendarUpdate = 0;

/// Updates the calendar if necessary.
void updateCalendar() {
  if (millis() - lastCalendarUpdate > POLLING_INTERVAL_MS) {
    // do update
  }
}

void displayCalendar(Adafruit_SSD1306 display) {
  updateCalendar();
  // do display
}
