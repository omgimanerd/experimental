/// Header file for timer.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef TIMER_H
#define TIMER_H

void startTimer();
void pauseTimer();
void updateTimer();
void incrementTimer();
void decrementTimer();
void resetTimer();
void displayTimer(Adafruit_SSD1306 display);

#endif TIMER_H
