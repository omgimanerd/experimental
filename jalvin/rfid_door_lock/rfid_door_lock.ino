/*
 * Controller for James's door.
 * Author: Alvin Lin (alvin@omgimanerd.tech)
 */

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9
#define SS_PIN 10
#define NUM_ACCESS_CODES 2
#define CODE_LENGTH 10

#define STEP_GROUND_PIN 3
#define STEP_POWER_PIN 4
#define STEP_DIRECTION_PIN 5
#define STEPS_PER_REV 200

#define LED_GROUND A4
#define LED_POWER A5

MFRC522 rfid(SS_PIN, RST_PIN);

/**
 * The valid UID access bits.
 */
const byte ACCESS[NUM_ACCESS_CODES][CODE_LENGTH] = {
  { 11, 87, 11, 35, 0, 0, 0, 0, 0, 0 },
  { 229, 50, 174, 41, 0, 0, 0, 0, 0, 0 }
};

/**
 * We'll be hardcoding the correct card UID into the program.
 * Obviously not secure, but who the fuck is going to hack this?
 */
bool authenticate(byte input[]) {
  for (int code = 0; code < NUM_ACCESS_CODES; ++code) {
    for (int i = 0; i < CODE_LENGTH; ++i) {
      if (input[i] != ACCESS[code][i]) {
        break;
      }
    }
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  rfid.PCD_Init(); // Initialize RFID reader

  pinMode(STEP_GROUND_PIN, OUTPUT);
  pinMode(STEP_POWER_PIN, OUTPUT);
  pinMode(STEP_DIRECTION_PIN, OUTPUT);
  digitalWrite(STEP_GROUND_PIN, LOW);
  digitalWrite(STEP_POWER_PIN, LOW);
  digitalWrite(STEP_DIRECTION_PIN, LOW);

  pinMode(LED_GROUND, OUTPUT);
  pinMode(LED_POWER, OUTPUT);
  digitalWrite(LED_GROUND, LOW);
  digitalWrite(LED_POWER, LOW);
}

void loop() {
//  if (rfid.PICC_IsNewCardPresent()) {
//    if (rfid.PICC_ReadCardSerial()) {
//      if (authenticate(rfid.uid.uidByte)) {
//        delay(1000);
//      }
//    }
//  }
  digitalWrite(STEP_POWER_PIN, HIGH);
  delay(5);
  digitalWrite(STEP_POWER_PIN, LOW);
  delay(5);
}


