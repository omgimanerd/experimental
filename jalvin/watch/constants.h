/// File for storing global constants.
/// Author: Alvin Lin (alvin@omgimanerd.tech)

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ANALOG_LIMIT   1023
#define TAU            6.28
#define VOLTAGE_MAX     3.3
#define VOLTAGE_SLEEP  3.75
#define VOLTAGE_EPSILON 0.5

#define TITLE_TEXT_X      0
#define TITLE_TEXT_Y      5

// Pins of connected components.
#define LEFT_BUTTON       2
#define MIDDLE_BUTTON     3
#define RIGHT_BUTTON      4
#define OLED_RESET       10
#define VIBRATION_MOTOR  11
#define LASER            12
#define BOARD_LED        13
#define POTENTIOMETER    A0
#define BATTERY          A3

// For button states and their indexes in the array of button structs
#define NUM_BUTTONS       3
#define LEFT              0
#define MIDDLE            1
#define RIGHT             2

#endif CONSTANTS_H
