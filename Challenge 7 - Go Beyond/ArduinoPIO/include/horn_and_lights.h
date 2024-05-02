#ifndef __HORN_LIGHTS__ 
#define __HORN_LIGHTS__

#include <Arduino.h>
#include "pins.h"

// initializes hornPin to Output
void setup_horn(); 
void setup_lights(); 
void honk(); 
void honk_times(int num_times); 

#endif 