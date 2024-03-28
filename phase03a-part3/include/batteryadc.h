/* Authors: Chris Bann and Remy Ren
 *
 * 
 */

#include <Arduino.h>
#define RUN_SUCCESS 1
#define RUN_FAILURE 0

int batterySetup(void);

int readADC(void);

double calculateVoltage(int adcValue, double refVoltage);

int publishBattery(double calculatedVoltage, bool alsoPercent);

int printBattery(double calculatedVoltage);

int displayBatteryLED(double calculatedVoltage);