/// Module for displaying and maintaining a stopwatch.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "constants.h"

#include "stopwatch.h"

bool stopWatchRunning = false;
long timeStarted = -1;
long timePassed = 0;

/// Starts/resumes the stopwatch.
void startStopwatch() {
  stopWatchRunning = true;
  if (timeStarted == -1) {
    timeStarted = millis();
  }
}

/// Pauses the stopwatch.
void pauseStopwatch() {
  stopWatchRunning = false;
}

/// Resets the stopwatch.
void resetStopwatch() {
  if (!stopWatchRunning) {
    timePassed = 0;
    timeStarted = -1;
  }
}

/// Method called internally every update loop to update the stopwatch
/// variables.
void updateStopwatch() {
  if (stopWatchRunning) {
    timePassed = millis() - timeStarted;
  }
}

void updateStopwatchOnInput(bool buttons[3][3]) {
  if (buttons[MIDDLE][TOGGLE]) {
    if (stopWatchRunning) {
      pauseStopwatch();
    } else {
      startStopwatch();
    }
  } else if (buttons[LEFT][TOGGLE]) {
    resetStopwatch();
  }
}

/// Draws the state of the stopwatch onto the face of the display.
void displayStopwatch(Adafruit_SSD1306 display) {
  short milliseconds = timePassed % 1000;
  short seconds = (timePassed / 1000) % 60;
  short minutes = (timePassed / 1000) / 60;

  char timeBuffer[TIME_BUFFER_SIZE];

  display.setCursor(0, 5);
  display.setTextSize(1);
  display.print(F("Stopwatch"));

  display.setCursor(STOPWATCH_MS_X, STOPWATCH_MS_Y);
  sprintf(timeBuffer, "%03d", milliseconds);
  display.print(timeBuffer);

  display.setCursor(STOPWATCH_M_S_X, STOPWATCH_M_S_Y);
  display.setTextSize(2);
  sprintf(timeBuffer, "%5d:%02d", minutes, seconds);
  display.print(timeBuffer);
}
