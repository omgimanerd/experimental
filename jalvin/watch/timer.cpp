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
static unsigned int lastHoldTime = HOLD_INCR_DECR_TIME;

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
void incrementTimer(unsigned int ms) {
  timerMilliseconds += ms;
}

/// Decrements the timer value.
void decrementTimer(unsigned int ms) {
  if (timerMilliseconds < ms) {
    timerMilliseconds = 0;
  } else {
    timerMilliseconds -= ms;
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
    if (buttons[LEFT].hold > lastHoldTime) {
      decrementTimer(MAJOR_INCR_DECR_AMOUNT);
      lastHoldTime += HOLD_INCR_DECR_INTERVAL;
    } else if (buttons[LEFT].onUp) {
      decrementTimer(MINOR_INCR_DECR_AMOUNT);
    } else if (buttons[RIGHT].hold) {
      incrementTimer(MAJOR_INCR_DECR_AMOUNT);
      lastHoldTime += HOLD_INCR_DECR_INTERVAL;
    } else if (buttons[RIGHT].onUp) {
      incrementTimer(MINOR_INCR_DECR_AMOUNT);
    } else {
      lastHoldTime = HOLD_INCR_DECR_TIME;
    }
  }
}

/// Draws the timer onto the display.
void displayTimer(Adafruit_SSD1306 display) {
  short milliseconds = timerMilliseconds % 1000;
  short seconds = (timerMilliseconds / 1000) % 60;
  short minutes = (timerMilliseconds / 1000) / 60;

  char timeBuffer[TIME_BUFFER_SIZE];

  display.setCursor(TITLE_TEXT_X, TITLE_TEXT_Y);
  display.print(F("Timer"));

  display.setCursor(TIMER_MS_X, TIMER_MS_Y);
  sprintf(timeBuffer, "%03d", milliseconds);
  display.print(timeBuffer);

  display.setCursor(TIMER_M_S_X, TIMER_M_S_Y);
  display.setTextSize(2);
  sprintf(timeBuffer, "%5d:%02d", minutes, seconds);
  display.print(timeBuffer);
}
