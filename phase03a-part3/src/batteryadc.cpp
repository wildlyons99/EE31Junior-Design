/* Authors: Chris Bann and Remy Ren
 * 
 * 
 */

#include <Arduino.h>


int batteryPinSetup(int &pinArray, int numberOfPins) {
    for (i = 0; i < numberOfPins; i++) {
        pinMode(pinArray[i], INPUT_PULLUP);
    }
}

int readADC(void) {
    readAnalog
}

double calculateVoltage(int adcValue, double refVoltage) {
    double referenceVoltage = refVoltage; // Assuming reference voltage is 9.0V
    double r1 = 2.0e6; // R1 = 2M ohms
    double r2 = 2.4e6; // R2 = 2.4M ohms

    double voltage = (adcValue * referenceVoltage) / 1024.0;
    double resistanceRatio = (r1 + r2) / r2;
    double calculatedVoltage = voltage * resistanceRatio;

    return calculatedVoltage;
}

void display 