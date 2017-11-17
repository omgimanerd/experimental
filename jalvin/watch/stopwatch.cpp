/// Module for displaying and maintaining a stopwatch.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#include "constants.h"

#include "stopwatch.h"

static bool stopWatchRunning = false;
static unsigned long timeStarted = -1;
static unsigned long timePassed = 0;

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

/// Function called every update loop to update the stopwatch variables.
void updateStopwatch() {
  if (stopWatchRunning) {
    timePassed = millis() - timeStarted;
  }
}

/// Updates the stopwatch's state based on the well-defined button state array.
void updateStopwatchOnInput(unsigned int buttons[BUTTONS][STATES]) {
  if (buttons[MIDDLE][ON_DOWN]) {
    if (stopWatchRunning) {
      pauseStopwatch();
    } else {
      startStopwatch();
    }
  } else if (buttons[LEFT][ON_DOWN]) {
    resetStopwatch();
  }
}

/// Draws the stopwatch onto the display.
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
