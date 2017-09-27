#include <Servo.h>

#define SERVO_PIN 9
#define POT A0

Servo esc;
 
void setup() {
  esc.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {
  int throttle = analogRead(POT);
  throttle = map(throttle, 0, 1023, 0, 179);
  Serial.println(throttle);
  esc.write(throttle);
}
