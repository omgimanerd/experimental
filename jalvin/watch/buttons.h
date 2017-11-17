/// Header file for buttons.cpp
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef BUTTONS_H
#define BUTTONS_H

typedef struct ButtonStruct {
  byte pin;
  bool state;
  bool onDown;
  bool onUp;
  bool last;
  unsigned int hold;
} Button;

void updateButtonState(Button* button, unsigned int deltaTime);

#endif
