#ifndef __TEAMRED_PINS__
#define __TEAMRED_PINS__

////////////////////////////////////////////////
//             Analog pins                    //
////////////////////////////////////////////////

// Ambient Light
#define photoresistor_pin A2
// Collision Detection
#define COLLISION_PIN A4
// color Detection
#define colorRead A5


/////////////////////////////////////////////////
//             Digital pins                    //
/////////////////////////////////////////////////

// PWM pin options: 3, 5, 6, 9, 10 and 11

const int headlights = 1; 
const int brake = 2; 

const int right_blinker = 3; 
const int left_blinker = 4;  

// Light and horns //TODO UH OH OVERLAP
const int hornPin = 4; // Output pin for the square wave

// Motor B connections
const int motorB1 = 6;
const int motorB2 = 5;

// Color Detection Pin Values
const int redLED = 7;
const int blueLED = 8;

// Motor A connections
const int motorA1 = 10; // pwn pin
const int motorA2 = 9; // pwn pin 


#endif