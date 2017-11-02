#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int x = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  display.drawLine(x % 128, 10, (x + 5) % 128, 10, WHITE);
  display.display();
  delay(250);
  x++;
}
