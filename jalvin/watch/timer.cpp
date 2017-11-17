/// Module for displaying and maintaining a timer.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Adafruit_SSD1306.h>

#include "buttons.h"
#include "constants.h"

#include "timer.h"

static bool timerRunning = false;
static unsigned long timerMilliseconds = 0;
static unsigned long lastUpdateTime = 0;
static unsigned long lastVibrateTime = 0;

/// Starts/resumes the timer.
void startTimer() {
  if (timerMilliseconds != 0) {
    timerRunning = true;
    lastUpdateTime = millis();
  }
}

/// Pauses the timer.
void pauseTimer() {
  timerRunning = false;
}

/// Increments the timer value.
void incrementTimer() {
  timerMilliseconds += 1000;
}

/// Decrements the timer value.
void decrementTimer() {
  if (timerMilliseconds < 1000) {
    timerMilliseconds = 0;
  } else {
    timerMilliseconds -= 1000;
  }
}

/// Resets the timer back to 0.
void resetTimer() {
  timerMilliseconds = 0;
}

/// Function called every update loop to update the timer variables.
void updateTimer() {
  unsigned long currentTime = millis();
  int deltaTime = currentTime - lastUpdateTime;
  if (timerRunning) {
    if (deltaTime > timerMilliseconds) {
      timerMilliseconds = 0;
      timerRunning = false;
      lastVibrateTime = currentTime;
    } else {
      timerMilliseconds -= deltaTime;
    }
  }
  if (currentTime - lastVibrateTime < VIBRATE_DURATION) {
    digitalWrite(VIBRATION_MOTOR, HIGH);
  } else {
    digitalWrite(VIBRATION_MOTOR, LOW);
  }
  lastUpdateTime = currentTime;
}

/// Updates the timer's state based on the well-defined button state array.
void updateTimerOnInput(Button buttons[NUM_BUTTONS]) {
  if (buttons[MIDDLE].hold > RESET_HOLD_TIME) {
    resetTimer();
  } else if (buttons[MIDDLE].onUp) {
    if (timerRunning) {
      pauseTimer();
    } else {
      startTimer();
    }
  } else if (!timerRunning) {
    if (buttons[LEFT].onDown) {
      decrementTimer();
    } else if (buttons[RIGHT].onDown) {
      incrementTimer();
    }
  }
}

/// Draws the timer onto the display.
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
