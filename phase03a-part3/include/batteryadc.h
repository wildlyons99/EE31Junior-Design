/* Authors: Chris Bann and Remy Ren
 *
 * 
 */

#include <Arduino.h>
#define RUN_SUCCESS 1
#define RUN_FAILURE 0

int8_t batteryPinSetup(int pinArray[], int numberOfPins);

int8_t pinsLEDSetup(int pinArray[], int numberOfPins);

int readADC(int pinValue, int &adcValue);

double calculateVoltage(int adcValue, double refVoltage);

uint8_t calculateMappedPercent(double calculatedVoltage, double min, double max);

void displayPercentLED(int percent, int pinArray[]);

uint8_t getPercent(double min, double max, int pinADC);

uint8_t getPercentDisplayLED(double min, double max, int pinADC, int pinsLED[]);