/* Authors: Chris Bann and Remy Ren
 *
 * 
 */

#include <Arduino.h>
#define RUN_SUCCESS 1
#define RUN_FAILURE 0

int batteryPinSetup(int &pinArray, int numberOfPins);

int readADC(int pinValue, int &adcValue);

double calculateVoltage(int adcValue, double refVoltage);

int calculateMappedPercent(double calculatedVoltage, double min, double max);

int displayPercentLED(int percent, int &pinArray);