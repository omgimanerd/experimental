/// Module for displaying and maintaining a timer.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

#include "constants.h"

#include "timer.h"

bool timerRunning = false;
long timerMilliseconds = 0;
long lastUpdateTime = 0;

void startTimer() {
  timerRunning = true;
  lastUpdateTime = millis();
}

void pauseTimer() {
  timerRunning = false;
}

void incrementTimer() {
  timerMilliseconds += 1000;
}

void decrementTimer() {
  timerMilliseconds -= 1000;
  if (timerMilliseconds < 0) {
    timerMilliseconds = 0;
  }
}

void resetTimer() {
  if (!timerRunning) {
    timerMilliseconds = 0;
  }
}

void updateTimer() {
  if (timerRunning) {
    short deltaTime = millis() - lastUpdateTime;
    timerMilliseconds -= deltaTime;
    if (timerMilliseconds < 0) {
      timerMilliseconds = 0;
      timerRunning = false;
    }
  }
  lastUpdateTime = millis();
}

void updateTimerOnInput(bool buttons[3][3]) {
  if (buttons[MIDDLE][TOGGLE]) {
    if (timerRunning) {
      pauseTimer();
    } else {
      startTimer();
    }
  }
  if (!timerRunning) {
    if (buttons[LEFT][TOGGLE]) {
      decrementTimer();
    } else if (buttons[RIGHT][TOGGLE]) {
      incrementTimer();
    }
  }
}

void displayTimer(Adafruit_SSD1306 display) {
  short milliseconds = timerMilliseconds % 1000;
  short seconds = (timerMilliseconds / 1000) % 60;
  short minutes = (timerMilliseconds / 1000) / 60;

  char timeBuffer[TIME_BUFFER_SIZE];

  display.setCursor(0, 5);
  display.setTextSize(1);
  display.print(F("Timer"));

  display.setCursor(TIMER_MS_X, TIMER_MS_Y);
  sprintf(timeBuffer, "%03d", milliseconds);
  display.print(timeBuffer);

  display.setCursor(TIMER_M_S_X, TIMER_M_S_Y);
  display.setTextSize(2);
  sprintf(timeBuffer, "%5d:%02d", minutes, seconds);
  display.print(timeBuffer);
}
