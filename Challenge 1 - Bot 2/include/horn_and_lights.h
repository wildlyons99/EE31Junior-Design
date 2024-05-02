#ifndef __HORN_LIGHTS__
#define __HORN_LIGHTS__

#include <Arduino.h>

// initializes hornPin to Output
void setup_horn();
void setup_lights();
void honk();
void honk_times(int num_times);
void flash_headlights();
void rear_turn_signal();
void morse_hi();
void BlinkRedStatus();
void BlinkGreenStatus();
void BlinkBlueStatus();
void BlinkYellowStatus();
void headAndRear();

#endif