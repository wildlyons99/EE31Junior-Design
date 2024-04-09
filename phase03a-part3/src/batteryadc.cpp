/* Authors: Chris Bann and Remy Ren
 * Library to read the battery percentage value.
 */

#define RTN_SUCCESS 0
#define RTN_FAILURE -1

#include <Arduino.h>

/// @brief Set all pins to be observed by ADC
/// @param int pinArray[]
/// @param int numberOfPins 
/// @return int8_t for error checking
int8_t batteryPinSetup(int pinArray[], int numberOfPins) {
    for (int i = 0; i < numberOfPins; i++) {
        pinMode(pinArray[i], INPUT);
    }
    return RTN_SUCCESS;
}

/// @brief Set all pins to be used for LEDs
/// @param int pinArray[]
/// @param int numberOfPins 
/// @return int8_t for error checking
int8_t pinsLEDSetup(int pinArray[], int numberOfPins) {
    for (int i = 0; i < numberOfPins; i++) {
        pinMode(pinArray[i], OUTPUT);
    }
    return RTN_SUCCESS;
}

/// @brief Reads and gives the ADC value for a pin (A0 to A5)
/// @param int pinValue
/// @param int &adcValue 
/// @return integer ADC value
int readADC(int pinValue, int &adcValue) {
    adcValue = analogRead(pinValue);
    return RTN_SUCCESS;
}

/// @brief Returns a calculated voltage based on the ADC value.
/// @param int adcValue
/// @param double refVoltage
/// @return double calculatedVoltage
double calculateVoltage(int adcValue, double refVoltage) {
    double referenceVoltage = refVoltage; // Assuming reference voltage is 9.0V
    double r1 = 2.0e6; // R1 = 2M ohms
    double r2 = 2.4e6; // R2 = 2.4M ohms

    double voltage = (adcValue * referenceVoltage) / 1024.0;
    double resistanceRatio = (r1 + r2) / r2;
    double calculatedVoltage = voltage * resistanceRatio;

    return calculatedVoltage;
}

/// @brief Returns the battery percentage from a voltage.
/// @param double calculatedVoltage
/// @param double min
/// @param double max
/// @return uint8_t percent
uint8_t calculateMappedPercent(double calculatedVoltage, double min, double max) {
    return map(calculatedVoltage, min, max, 0, 100);
}

/// @brief  Displays the current battery percentage via 3 LEDs -> Low, Med, High
/// @param  int percent (0 to 100)
/// @param  int pinArray[] -> [0] Low, [1] Medium, [2] High 
/// @return none
void displayPercentLED(int percent, int pinArray[]) {
    // this is stupid, it doesn't run faster but it works.
    // The modulo math will give the LED in 3 stages.
    int pinToWrite = map(percent, 0, 100, 3, 5);
    digitalWrite(pinArray[0], !(3 % pinToWrite)); // Low
    digitalWrite(pinArray[1], !(4 % pinToWrite)); // Medium
    digitalWrite(pinArray[2], !(5 % pinToWrite)); // High
}

/// @brief  Get and return the battery percentage.
/// @param  int pinADC, of the ADC pin you wish to read
/// @param  int pinsLED[] -> [0] Low, [1] Medium, [2] High 
/// @return uint8_t percent
uint8_t getPercent(double min, double max, int pinADC) {
    int adcValue = 0;
    readADC(pinADC, adcValue);
    double calculatedVoltage = calculateVoltage(adcValue, 9.0); // Assuming 9.0V ref. voltage.
    int percent = calculateMappedPercent(calculatedVoltage, min, max);
    return percent;
}

/// @brief  Get and display battery percentage via LED for a particular pin.
/// @param  int pinADC, of the ADC pin you wish to read
/// @param  int pinsLED[] -> [0] Low, [1] Medium, [2] High 
/// @return uint8_t percent
uint8_t getPercentDisplayLED(double min, double max, int pinADC, int pinsLED[]) {
    int percent = getPercent(min, max, pinADC);
    displayPercentLED(percent, pinsLED);
    return percent;
}