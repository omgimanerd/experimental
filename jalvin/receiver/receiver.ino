#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

RH_ASK driver;

int count = 0;

void setup()
{
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    if (!driver.init())
         Serial.println("init failed");
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.display();
    display.clearDisplay();
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      if (String((char*)buf).substring(0,4) == "Left") {
        Serial.println("Go left");      
        count--;   
      }
      else if (String((char*)buf).substring(0,5) == "Right") {
        Serial.println("Go right");
        count++;
      }
    }
    display.setCursor(0,0);
    display.print("Slide: ");
    display.println(count);
    display.println();
    display.print(millis()/1000/60);
    display.print(":");
    if ((millis()/1000)%60 < 10) {
      display.print("0");
    }
    display.println((millis()/1000)%60);
    display.display();
    display.clearDisplay();
}
