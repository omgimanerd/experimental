/// Header file for timer.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef TIMER_H
#define TIMER_H

#define TIMER_M_S_X   0
#define TIMER_M_S_Y  30
#define TIMER_MS_X   77
#define TIMER_MS_Y   50

#define TIME_BUFFER_SIZE 9

void startTimer();
void pauseTimer();
void updateTimer();
void incrementTimer();
void decrementTimer();
void resetTimer();

void updateTimer();
void updateTimerOnInput(bool buttons[3][3]);
void displayTimer(Adafruit_SSD1306 display);

#endif TIMER_H
