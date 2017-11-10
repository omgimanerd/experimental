/**
 * @author Alvin Lin (alvin.lin@stuypulse.com)
 * Header file that manages a stopwatch.
 */

boolean stopWatchRunning = false;

long timeStarted;
long timePassed;

void startTimer() {
  stopWatchRunning = true;
  timeStarted = millis();
}

void updateStopWatch() {
  if (stopWatchRunning) {
    timePassed = millis() - timeStarted;
  }
}

void stopTimer() {
  stopWatchRunning = false;
}

void resetTimer() {
  timePassed = 0;
}

void displayStopWatch() {
  display.setCursor(0, 30);
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

void updateStopWatchState() {
  if (stopWatchRunning) {
    stopTimer();
  } else if (timePassed == 0) {
    startTimer(); 
  } else {
    resetTimer();
  }
}
