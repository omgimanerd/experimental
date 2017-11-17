/// Header file for calendar.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CALENDAR_H
#define CALENDAR_H

#define MAX_EVENT_STRING_LENGTH 14

#define POLLING_INTERVAL_MS 60000

typedef struct EventStruct {
  unsigned long unixtime;
  char name[MAX_EVENT_STRING_LENGTH];
} Event;

void updateCalendar();
void displayCalendar(Adafruit_SSD1306 display);

#endif CALENDAR_H
