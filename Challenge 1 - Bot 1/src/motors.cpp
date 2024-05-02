/*****************************************************************
 *                      MOTORS   CODE                            *
 *****************************************************************/
#include <Arduino.h>

#include <motors.h>

#include "wifi_comm.h"

// A is right 
// B is left

// Set the speed (0 = off and 255 = max speed)
// will likely need to make seperate motor speed for A and B to match so:
const int forwardMotorSpeedA = 62; // 50% duty cycle
const int forwardMotorSpeedB = 60; // 50% duty cycle

const int turnRightMotorSpeedA = 65; // 50% duty cycle
const int turnRightMotorSpeedB = 70; // 50% duty cycle

// A is right
// B is left
const int backwardMotorSpeedA = 63;
const int backwardMotorSpeedB = 60;

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
    const char backwards[] = "$$$B1"; 
    send_mqtt(backwards); 
    analogWrite(motorA1, backwardMotorSpeedA);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, backwardMotorSpeedB);

    delay(delay_time);
    stop_all();
    const char stop_backwards[] = "$$$B0"; 
    send_mqtt(stop_backwards); 
}

void turn_right(int delay_time)
{
    const char right[] = "$$$R1"; 
    send_mqtt(right); 
    analogWrite(motorA1, turnRightMotorSpeedA);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, turnRightMotorSpeedB);
    analogWrite(motorB2, LOW);

    delay(delay_time);
    stop_all();

    const char stop_right[] = "$$$R0"; 
    send_mqtt(stop_right); 
}

void turn_left(int delay_time)
{
    const char left[] = "$$$L1"; 
    send_mqtt(left); 
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, turnRightMotorSpeedA);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, turnRightMotorSpeedB);

    delay(delay_time);
    stop_all();

    const char stop_left[] = "$$$L0"; 
    send_mqtt(stop_left); 
}

void stop_all()
{
    analogWrite(motorA1, LOW);
    analogWrite(motorA2, LOW);
    analogWrite(motorB1, LOW);
    analogWrite(motorB2, LOW);
}