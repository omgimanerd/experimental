#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte rxAddr[6] = "00001";

void setup() {
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
  delay(1000);
}

//#include <Servo.h>
//
//#define SERVO_PIN 9
//#define POT A0
//
//Servo esc;
// 
//void setup() {
//  esc.attach(SERVO_PIN);
//  Serial.begin(9600);
//}
//
//void loop() {
//  int throttle = analogRead(POT);
//  throttle = map(throttle, 0, 1023, 0, 179);
//  Serial.println(throttle);
//  esc.write(throttle);
//}

