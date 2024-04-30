/*****************************************************************
 *                      COLLISION DETETCION                      *
 *****************************************************************/

#include <Arduino.h>
#include <collision_detection.h>

// Collision dectection indo 
const float ADC_RESOLUTION = 5.0 / 1023.0; 
#define COLLISION_PIN A4

// may need to be changed with reflective serface 
const float THREE_INCH_VOLTAGE = 2.0;
const float TWO_INCH_VOLTAGE = 2.4; 
const float ONE_5_INCH_VOLTAGE = 3.5; 
const float ONE_INCH_VOLTAGE = 4.00; 

const float bigger = 1.2;


/* obsticle
 * Purpose: 
 *      Check whether or not there is an object detected in front of the bot
 * Returns: 
 *      Whether or not an obstacle is detected in front of the bot
 * Notes:
 *      Currently configured for 3 inches from the wall
 */ 
bool obsticle() {
    int sensorValue = analogRead(COLLISION_PIN); // Read the analog voltage value from pin A1
    float voltage = sensorValue * ADC_RESOLUTION; 

    // Serial.print(F("Senor value: ")); Serial.println(sensorValue); 
    // Serial.print(F("Voltage value: ")); Serial.println(voltage); 

    if (voltage >= bigger) {
        // Serial.println("Collision Detected"); 
        return true; 
    } else {
        return false; 
    }
}