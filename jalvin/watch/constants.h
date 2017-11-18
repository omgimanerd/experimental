/// File for storing global constants.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ANALOG_LIMIT  1023
#define TAU           6.28
#define VOLTAGE_MAX    3.3

#define TITLE_TEXT_X     0
#define TITLE_TEXT_Y     5

// Pins of connected components.
#define MIDDLE_BUTTON    2
#define LEFT_BUTTON      3
#define RIGHT_BUTTON     5
#define OLED_RESET       4
#define LASER            6
#define VIBRATION_MOTOR  7
#define POTENTIOMETER   A0
#define BATTERY         A1

// For button states and their indexes in the array of button structs
#define NUM_BUTTONS      3
#define LEFT             0
#define MIDDLE           1
#define RIGHT            2

#endif CONSTANTS_H
