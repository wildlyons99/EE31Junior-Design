// main.cpp
// Tom Lyons
// 
// EE31 Junior Design - phase 2B
// Tufts University 

#include <Arduino.h>

void go_forward(); 
void go_backwards(); 
void go_right(); 
void go_left(); 
void stop_all(); 


// PWM pin options: 3, 5, 6, 9, 10 and 11

// A is right
// B is left 
 
// Motor A connections
const int enableA = 9; // pwm pin
const int motorA1 = 5;
const int motorA2 = 6;
 
// Motor B connections
const int enableB = 10; // pwm pin
const int motorB1 = 7;
const int motorB2 = 8;
 
// Set the speed (0 = off and 255 = max speed)
// will likely need to make seperate motor speed for A and B to match so: 
const int motorSpeedA = 135; // 50% duty cycle 
const int motorSpeedB = 120; // 50% duty cycle 
 
void setup() {
    // Set motor control pins to outputs
    pinMode(enableA, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    
    // Set motors off for initial state
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    
    // Set the motor speed with enable PWM 
    analogWrite(enableA, motorSpeedA); 
    analogWrite(enableB, motorSpeedB); 
}
 
void loop() {
    // Go forwards
    go_forward();
    delay(3000);
    
    // // Go backwards
    // go_backwards();
    // delay(3000);
    
    // // Go right
    // go_right();
    // delay(3000);
    
    // // Go left
    // go_left();
    // delay(3000);
    
    // Stop
    stop_all();
    delay(3000);
}
 
/*   
 *  Forwards, backwards, right, left, stop.
 */
void go_forward() {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
}

void go_backwards() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}

void go_right() {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}

void go_left() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
}

void stop_all() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}