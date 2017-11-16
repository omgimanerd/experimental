/// File for storing global constants.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ANALOG_LIMIT  1023
#define TAU           6.28
#define VOLTAGE_MAX    3.3

// Pins of connected components.
#define LASER            2
#define LEFT_BUTTON      3
#define RIGHT_BUTTON     5
#define OLED_RESET       4
#define MIDDLE_BUTTON    6
#define VIBRATION_MOTOR  7
#define POTENTIOMETER   A0
#define BATTERY         A1

// For button states and their indexes in the array.
#define BUTTONS          3
#define LEFT             0
#define MIDDLE           1
#define RIGHT            2

// The different states that the buttons can be in. This is well-defined so that
// each individual module can assume the button state array's existence and
// use its values.
#define STATES           5
#define STATE            0
#define ON_DOWN          1
#define ON_UP            2
#define HOLD             3
#define LAST             4

#endif CONSTANTS_H
