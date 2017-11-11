/// Module for displaying and maintaining a stopwatch.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "stopwatch.h"

bool stopWatchRunning = false;
long timeStarted;
long timePassed;

/// Starts the stopwatch.
void startStopwatch() {
  stopWatchRunning = true;
  timeStarted = millis();
}

/// Stops the stopwatch.
void stopStopwatch() {
  stopWatchRunning = false;
}

/// Resets the stopwatch.
void resetStopwatch() {
  timePassed = 0;
}

/// Toggles the stopwatch from stop to start to reset.
void toggleStopwatch() {
  if (stopWatchRunning) {
    stopStopwatch();
  } else if (timePassed == 0) {
    startStopwatch();
  } else {
    resetStopwatch();
  }
}

/// Method called internally every update loop to update the stopwatch
/// variables.
void updateStopwatch() {
  if (stopWatchRunning) {
    timePassed = millis() - timeStarted;
  }
}

/// Draws the state of the stopwatch onto the face of the display.
void displayStopwatch(Adafruit_SSD1306 display) {
  int milliseconds = timePassed % 1000;
  int seconds = (timePassed / 1000) % 60;
  int minutes = (timePassed / 1000) / 60;

  char timeBuffer[TIME_BUFFER_SIZE];
  sprintf(timeBuffer, "%5d:%02d", minutes, seconds, milliseconds);

  display.setCursor(STOPWATCH_M_S_X, STOPWATCH_M_S_Y);
  display.setTextSize(2);
  display.print(timeBuffer);

  display.setCursor(STOPWATCH_MS_X, STOPWATCH_MS_Y);
  display.setTextSize(1);
  sprintf(timeBuffer, "%03d", milliseconds);
  display.print(timeBuffer);
}
