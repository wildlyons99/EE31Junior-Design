/*****************************************************************
 *                      MOTORS   CODE                            *
 *****************************************************************/
#include <Arduino.h>

#include <motors.h>

#include "horn_and_lights.h"
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
const int forwardMotorSpeedA = 68; // 50% duty cycle
const int forwardMotorSpeedB = 70; // 50% duty cycle

const int turnRightMotorSpeedA = 65; // 50% duty cycle
const int turnRightMotorSpeedB = 70; // 50% duty cycle

// A is right
// B is left
const int backwardMotorSpeedA = 65;
const int backwardMotorSpeedB = 70;

void setup_motors()
{
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

/* drive forward
 * Will drive forward without stopping
 */
void drive_forward() {
    // Set the motor speed with enable PWM 
    analogWrite(enableA, forwardMotorSpeedA); 
    analogWrite(enableB, forwardMotorSpeedB); 
    // delay(10); 

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW); 
}

void go_forward(int delay_time)
{
    analogWrite(enableA, forwardMotorSpeedA);
    analogWrite(enableB, forwardMotorSpeedB);
    delay(10);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);

    delay(delay_time);
    stop_all();
}

void go_backwards(int delay_time)
{
    analogWrite(enableA, backwardMotorSpeedA);
    analogWrite(enableB, backwardMotorSpeedB);
    delay(10);

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);

    delay(delay_time);
    stop_all();
}

void turn_right(int delay_time)
{
    analogWrite(enableA, turnRightMotorSpeedA);
    analogWrite(enableB, turnRightMotorSpeedB);
    delay(10);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);

    delay(delay_time);
    stop_all();
}

void turn_left(int delay_time)
{
    analogWrite(enableA, turnRightMotorSpeedA);
    analogWrite(enableB, turnRightMotorSpeedB);
    delay(10);

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);

    delay(delay_time);
    stop_all();
}

void stop_all()
{
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}