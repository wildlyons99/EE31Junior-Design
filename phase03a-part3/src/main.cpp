// main.cpp
// Remy Ren
//
// EE31 Junior Design - Phase 3A
// Tufts University

#include <Arduino.h>
#include "batteryadc.h"

int logicPercent = 0;
int motorPercent = 0;
int pinLogic = A1;
int pinMotor = A0;
int pinsADC[] = {pinLogic, pinMotor};
int pinsLED[] = {11, 12, 13}; // Replace pins as needed. Low, Med, High.

void setup()
{
    // batteryPinSetup(pinsADC, 2);
    // pinsLEDSetup(pinsLED, 3);
    Serial.begin(9600);
    Serial.print("yay!\n");
}

void loop()
{
    motorPercent = getPercentDisplayLED(6.0, 9.0, pinMotor, pinsLED);
    Serial.print("Motor: ");
    Serial.print(motorPercent);
    Serial.print("%\n");
    // Serial.print("Hello World!\n");
    // logicPercent = getPercent(4.0, 5.0, pinLogic);
    // printf("Motor: %i%, Logic: %i%\n", motorPercent, logicPercent);
    delay(500);
}