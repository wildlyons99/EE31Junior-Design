#ifndef __BATTERY_ADC__
#define __BATTERY_ADC__

/* Authors: Chris Bann and Remy Ren
 * Library to read the battery percentage value.
 */

#include <Arduino.h>
#define RUN_SUCCESS 1
#define RUN_FAILURE 0

int8_t batteryPinSetup(int pinArray[], int numberOfPins);

int8_t pinsLEDSetup(int pinArray[], int numberOfPins);

int readADC(int pinValue, int &adcValue);

double calculateVoltage(int adcValue, double refVoltage);

uint8_t calculate5VMappedPercent(double min, double max, double calculatedVoltage);

void displayPercentLED(int percent, int pinArray[]);

uint8_t getPercent(double min, double max, int pinADC);

uint8_t getPercentDisplayLED(double min, double max, int pinADC, int pinsLED[]);


#endif