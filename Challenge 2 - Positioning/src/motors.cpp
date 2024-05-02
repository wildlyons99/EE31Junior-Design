/*****************************************************************
 *                      MOTORS   CODE                            *
 *****************************************************************/
#include <Arduino.h>

#include <motors.h>

// PWM pin options: 3, 5, 6, 9, 10 and 11

// A is right 
// B is left


// Motor A connections
const int motorA1 = 10; // pwn pin
const int motorA2 = 9; // pwn pin 

// Motor B connections
const int motorB1 = 6;
const int motorB2 = 5;

// Set the speed (0 = off and 255 = max speed)
// will likely need to make seperate motor speed for A and B to match so:
const int forwardMotorSpeedA = 53; // 50% duty cycle
const int forwardMotorSpeedB = 45; // 50% duty cycle

const int turnRightMotorSpeedA = 65; // 50% duty cycle
const int turnRightMotorSpeedB = 70; // 50% duty cycle

// A is right
// B is left
const int backwardMotorSpeedA = 51;
const int backwardMotorSpeedB = 45;

void setup_motors()
{
    // Set motor control pins to outputs
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    delay(100);
    
    // Set motors off for initial state
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, LOW);
}

/* drive forward
 * Will drive forward without stopping
 */
void drive_forward() {
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, forwardMotorSpeedA);
    analogWrite(motorB1, forwardMotorSpeedB);
    analogWrite(motorB2, LOW); 
}

void go_forward(int delay_time)
{
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, forwardMotorSpeedA);
    analogWrite(motorB1, forwardMotorSpeedB);
    analogWrite(motorB2, LOW);

    delay(delay_time);
    stop_all();
}

void go_backwards(int delay_time)
{
    analogWrite(motorA1, backwardMotorSpeedA);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, backwardMotorSpeedB);

    delay(delay_time);
    stop_all();
}

void turn_left(int delay_time)
{
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, turnRightMotorSpeedA);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, turnRightMotorSpeedB);

    delay(delay_time);
    stop_all();
}

void turn_right(int delay_time)
{
    analogWrite(motorA1, turnRightMotorSpeedA);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, turnRightMotorSpeedB);
    analogWrite(motorB2, LOW);

    delay(delay_time);
    stop_all();
}

void stop_all()
{
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, LOW);
}