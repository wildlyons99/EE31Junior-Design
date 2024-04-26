#ifndef __MOTORS__
#define __MOTORS__

#include <Arduino.h>

#define turn90 550

void setup_motors(); 

void go_forward(int delay_time); 
void turn_right(int delay_time); 
void turn_left(int delay_time); 
void stop_all(); 
void drive_forward(); 


#endif