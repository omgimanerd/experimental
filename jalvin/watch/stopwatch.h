/// Header file for stopwatch.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef STOPWATCH_H
#define STOPWATCH_H

#define STOPWATCH_M_S_X   0
#define STOPWATCH_M_S_Y  30
#define STOPWATCH_MS_X   77
#define STOPWATCH_MS_Y   50

#define TIME_BUFFER_SIZE  9

void startStopwatch();
void pauseStopwatch();
void resetStopwatch();

void updateStopwatch();
void updateStopwatchOnInput(bool buttons[3][3]);
void displayStopwatch(Adafruit_SSD1306 display);

#endif
