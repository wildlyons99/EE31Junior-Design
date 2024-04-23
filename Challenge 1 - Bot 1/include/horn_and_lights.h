#ifndef __HORN_LIGHTS__ 
#define __HORN_LIGHTS__

#include <Arduino.h>

const int hornPin = 4; // Output pin for the square wave

// initializes hornPin to Output
void setup_horn(); 
void honk(); 
void honk_times(int num_times); 

#endif 