/// Header file for timer.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef TIMER_H
#define TIMER_H

#define TIMER_M_S_X               0
#define TIMER_M_S_Y              30
#define TIMER_MS_X               77
#define TIMER_MS_Y               50

#define TIME_BUFFER_SIZE          9

#define VIBRATE_DURATION       1000
#define RESET_HOLD_TIME         500
#define HOLD_INCR_DECR_TIME    1000
#define HOLD_INCR_DECR_INTERVAL 500

void startTimer();
void pauseTimer();
void updateTimer();
void incrementTimer(unsigned int ms);
void decrementTimer(unsigned int ms);
void resetTimer();
void updateTimer();
void updateTimerOnInput(Button buttons[NUM_BUTTONS]);
void displayTimer(Adafruit_SSD1306 display);

#endif TIMER_H
