/// Module for displaying and maintaining a stopwatch.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "stopwatch.h"

bool stopWatchRunning = false;
long timeStarted;
long timePassed;

void startStopwatch() {
  stopWatchRunning = true;
  timeStarted = millis();
}

void updateStopwatch() {
  if (stopWatchRunning) {
    timePassed = millis() - timeStarted;
  }
}

void stopStopwatch() {
  stopWatchRunning = false;
}

void resetStopwatch() {
  timePassed = 0;
}

void toggleStopwatch() {
  if (stopWatchRunning) {
    stopStopwatch();
  } else if (timePassed == 0) {
    startStopwatch();
  } else {
    resetStopwatch();
  }
}

void displayStopwatch(Adafruit_SSD1306 display) {
  display.setCursor(STOPWATCH_X, STOPWATCH_Y);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  int milliseconds = timePassed % 1000;
  int seconds = (timePassed / 1000) % 60;
  int minutes = (timePassed / 1000) / 60;
  display.print(minutes);
  display.print(":");
  display.print(seconds);
  display.print(":");
  display.print(milliseconds);
}
