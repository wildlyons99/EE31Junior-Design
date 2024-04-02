/* Authors: Chris Bann and Remy Ren
 * Library to read the battery percentage value.
 * 
 */

#define RTN_SUCCESS 0
#define RTN_FAILURE -1

#include <Arduino.h>

/// @brief Set all pins to be observed by ADC
/// @param int &pinArray 
/// @param int numberOfPins 
/// @return int8_t for error checking
int8_t batteryPinSetup(int &pinArray, int numberOfPins) {
    for (i = 0; i < numberOfPins; i++) {
        pinMode(pinArray[i], INPUT_PULLUP);
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

/// @brief 
/// @param int adcValue
/// @param double refVoltage
/// @return 
double calculateVoltage(int adcValue, double refVoltage) {
    double referenceVoltage = refVoltage; // Assuming reference voltage is 9.0V
    double r1 = 2.0e6; // R1 = 2M ohms
    double r2 = 2.4e6; // R2 = 2.4M ohms

    double voltage = (adcValue * referenceVoltage) / 1024.0;
    double resistanceRatio = (r1 + r2) / r2;
    double calculatedVoltage = voltage * resistanceRatio;

    return calculatedVoltage;
}

// https://forum.arduino.cc/t/battery-level-interpretation/1103521/36 MAP PERCENTAGE!
double calculateMappedPercent() {

}

/// @brief  Sets which LED pins to display battery percent Low, Med, High
/// @param  int &pinArray -> [0] Low, [1] Medium, [2] High 
/// @param  int numberOfPins
/// @return none
void displayPercentLED() {

} 

/// @brief  Displays the current battery percentage via 3 LEDs -> Low, Med, High
/// @param  int &pinArray -> [0] Low, [1] Medium, [2] High 
/// @param  int numberOfPins
/// @param  double percent
/// @return none
void displayPercentLED(double percent) {
    if {

    }
    else if {

    }
    else if {

    }
    else {

    }
} 