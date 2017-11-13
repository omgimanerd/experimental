/// Module for displaying and maintaining a timer.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

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

void updateTimer() {
  if (timerRunning) {
    short deltaTime = millis() - lastUpdateTime;
    timerMilliseconds -= deltaTime;
    if (timerMilliseconds < 0) {
      timerMilliseconds = 0;
      timerRunning = false;
    }
  }
}

void incrementTimer() {

}

void decrementTimer() {

}

void resetTimer() {

}

void displayTimer(Adafruit_SSD1306 display) {
  short milliseconds = timerMilliseconds % 1000;
  short seconds = (timerMilliseconds / 1000) % 60;
  short minutes = (timerMilliseconds / 1000) / 60;
}
