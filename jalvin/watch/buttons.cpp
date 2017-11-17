/// Module for updating button states.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#include <Arduino.h>

#include "buttons.h"

/// Updates the button struct with the appropriate new data.
void updateButtonState(Button* button, unsigned int deltaTime) {
  button->state = digitalRead(button->pin) == LOW;
  button->onDown = button->state && (button->state != button->last);
  button->onUp = !button->state && (button->state != button->last);
  if (button->state) {
    button->hold += deltaTime;
  } else {
    button->hold = 0;
  }
  button->last = button->state;
}
