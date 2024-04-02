// main.cpp
// Tom Lyons
// 
// EE31 Junior Design - phase 2B
// Tufts University 

#include <Arduino.h>

void go_forward(int delay_time); 
void go_backwards(int delay_time); 
void go_right(int delay_time); 
void go_left(int delay_time); 
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
const int forwardMotorSpeedA = 70; // 50% duty cycle 
const int forwardMotorSpeedB = 90; // 50% duty cycle 


const int turnRightMotorSpeedA = 74; // 50% duty cycle 
const int turnRightMotorSpeedB = 98; // 50% duty cycle 

// A is right
// B is left 
const int backwardMotorSpeedA = 64; 
const int backwardMotorSpeedB = 57; 
 
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
    
    
}
 
void loop() {

    // Go forwards
    go_forward(3000);

    delay(1000); 
    
    // Go backwards
    go_backwards(3000);

    delay(1000); 
    
    // Go right
    go_right(775);

    delay(1000); 
    
    // // Go left
    go_left(860);

    delay(3000); 
}
 
/*   
 *  Forwards, backwards, right, left, stop.
 */
void go_forward(int delay_time) {
    // Set the motor speed with enable PWM 
    analogWrite(enableA, forwardMotorSpeedA); 
    analogWrite(enableB, forwardMotorSpeedB); 
    delay(10); 

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);

    delay(delay_time); 
    stop_all(); 
}

void go_backwards(int delay_time) {
    analogWrite(enableA, backwardMotorSpeedA); 
    analogWrite(enableB, backwardMotorSpeedB); 
    delay(10);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);

    delay(delay_time); 
    stop_all(); 
}

void go_right(int delay_time) {
    analogWrite(enableA, turnRightMotorSpeedA); 
    analogWrite(enableB, turnRightMotorSpeedB); 
    delay(10);

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);

    delay(delay_time); 
    stop_all(); 
}

void go_left(int delay_time) {
    analogWrite(enableA, turnRightMotorSpeedA); 
    analogWrite(enableB, turnRightMotorSpeedB); 
    delay(10);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);

    delay(delay_time); 
    stop_all(); 
}

void stop_all() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}