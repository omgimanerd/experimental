/// Header file for clock.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CLOCK_H
#define CLOCK_H

#define SECONDS_TO_RADIANS 0.1047
#define MINUTES_TO_RADIANS 0.1047
#define HOURS_TO_RADIANS 0.5236

#define CLOCK_RADIUS 27
#define CLOCK_X 30
#define CLOCK_Y 31
#define HOUR_HAND_LENGTH 12
#define MINUTE_HAND_LENGTH 17
#define SECOND_HAND_LENGTH 27
#define TICK_LENGTH 40

void displayAnalogClock(Adafruit_SSD1306 display, DateTime t);
void displayDigitalClock(Adafruit_SSD1306 display, DateTime t);

#endif
