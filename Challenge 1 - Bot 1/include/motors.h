#ifndef __MOTORS__
#define __MOTORS__

#include <Arduino.h>

// Motor A connections
const int motorA1 = 10; // pwn pin
const int motorA2 = 9; // pwn pin 

// Motor B connections
const int motorB1 = 6;
const int motorB2 = 5;

void setup_motors(); 

void go_forward(int delay_time); 
void turn_right(int delay_time); 
void turn_left(int delay_time); 
void stop_all(); 
void drive_forward(); 


#endif