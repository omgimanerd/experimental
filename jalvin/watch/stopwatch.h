/// Header file for stopwatch.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef STOPWATCH_H
#define STOPWATCH_H

#define STOPWATCH_X 0
#define STOPWATCH_Y 30

void startStopwatch();
void updateStopwatch();
void stopStopwatch();
void resetStopwatch();
void toggleStopwatch();
void displayStopwatch(Adafruit_SSD1306 display);

#endif
