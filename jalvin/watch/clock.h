/// Header file for clock.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CLOCK_H
#define CLOCK_H

#define TAU              6.28

#define CLOCK_RADIUS       30
#define CLOCK_X            30
#define CLOCK_Y            31
#define HOUR_HAND_LENGTH   10
#define MINUTE_HAND_LENGTH 20
#define TICK_DISTANCE       3
#define TICK_LENGTH         2

#define WAKE_LENGTH_MS   5000

#define DAY_OF_WEEK_X      68
#define DAY_OF_WEEK_Y      12
#define DATE_X             68
#define DATE_Y             22
#define TIME_X             68
#define TIME_Y             35

#define DATE_BUFFER_SIZE   11
#define TIME_BUFFER_SIZE    6

// void updateClockFace(DateTime t, bool wake);
// void displayClockFace(Adafruit_SSD1306 display);
void displayAnalogClock(Adafruit_SSD1306 display, DateTime now);

#endif
