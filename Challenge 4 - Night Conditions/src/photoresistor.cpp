/* Authors: Chris Bann and Remy Ren
 * Library to check ambient light/light values based on a photoresistor.
 */

#include <Arduino.h>
#include "photoresistor.h"

/// @brief Reads and gives the ADC value for a pin (A0 to A5)
/// @param int pinValue
/// @return integer ADC value
int readADC(int pinValue)
{
    return analogRead(pinValue);
}

/// @brief Returns a calculated voltage based on the ADC, for photoresistor.
/// @param int pinValue
/// @param int adcValue
/// @param double refVoltage
/// @return double calculatedVoltage
double calculateVoltage(int pinValue)
{
    int adcValue = analogRead(pinValue);
    return map(adcValue, 0.0, 1024.0, 0.0, 5.0);
}
