/**
 * Code powering our electric longboard. For reference, the servo angle maps to
 * a power for the brushless motor. During calibration and run, 0 - 90 is used
 * to calibrate and afterwards, 90 represents no power, and 180 represents full
 * power.
 */

#include <Servo.h>

#define MOTOR_PIN 9
#define POTENTIOMETER_PIN A0
#define BUTTON_PIN A1

// Units per millisecond
#define MIN_POWER 90
#define MAX_POWER 180
#define POWER_DECAY_RATE 0.025

// Initialize the driving motor
Servo motor;

// State variables
float currentPower = MIN_POWER;
long lastUpdateTime = 0;
float deltaTime = 0;

/**
 * Steps the motor from the starting power to the ending power with the given
 * delay between each step.
 * @param motor The motor to step
 * @param startPower The starting power
 * @param endPower The ending power
 * @param delayMs The delay between each step
 */
void stepPower(Servo motor, int startPower, int endPower, int delayMs) {
  if (startPower < endPower) {
    for (int i = startPower; i <= endPower; ++i) {
      motor.write(i);
      delay(delayMs);
    }
  } else {
    for (int i = startPower; i >= endPower; --i) {
      motor.write(i);
      delay(delayMs);
    }
  }
}

void initialize() {
  // This initial delay allows everything to start up before we begin
  // calibration
  delay(2000);
  stepPower(motor, 90, 0, 2);
  delay(200);
  stepPower(motor, 0, 90, 2);
  delay(4500);
  stepPower(motor, 90, 0, 2);
}

void setup() {
  Serial.begin(9600);

  motor.attach(MOTOR_PIN);
  initialize();

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
}

void loop() {
  int throttle = analogRead(POTENTIOMETER_PIN);
  throttle = map(throttle, 0, 1023, MIN_POWER, MAX_POWER);
  int button = digitalRead(BUTTON_PIN);

  long currentTime = micros();
  deltaTime = (currentTime - lastUpdateTime) / 1000;
  lastUpdateTime = currentTime;

  /**
   * If the button is pressed, we set that to the throttle, otherwise we
   * start scaling down the power (coasting).
   */
  if (!button) {
    currentPower = throttle;
  } else {
    currentPower = max(
      MIN_POWER, currentPower - (deltaTime * POWER_DECAY_RATE));
  }
  Serial.println(currentPower);

  motor.write((int) currentPower);
}
