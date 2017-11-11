#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

const int leftButton = 9;
const int rightButton = 8;

int buttonPushCounter = 1;
int buttonState = 0;
int lastButtonState = 0;

int otherbuttonPushCounter = 1;
int otherbuttonState = 0;
int otherlastButtonState = 0;

void setup()
{
    Serial.begin(9600);
    if (!driver.init())
         Serial.println("init failed");
    pinMode(leftButton, INPUT);
    pinMode(rightButton, INPUT);
    digitalWrite(2, HIGH);
}

void loop()
{
    const char *msg = "Left";
    const char *msg2 = "Right";
    Serial.println(otherbuttonPushCounter);
    Serial.println("1");
    buttonState = digitalRead(leftButton);
    otherbuttonState = digitalRead(rightButton);
    Serial.println("2");

    if (buttonState != lastButtonState) {
      if (buttonState == LOW) {
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        buttonPushCounter++;
      }
      delay(50);
    }
    lastButtonState = buttonState;
    Serial.println("3");

    if (otherbuttonState != otherlastButtonState) {
      if (otherbuttonState == LOW) {
        driver.send((uint8_t *)msg2, strlen(msg2));
        driver.waitPacketSent();
        otherbuttonPushCounter++;
      }
      delay(50);
    }
    otherlastButtonState = otherbuttonState;
}
