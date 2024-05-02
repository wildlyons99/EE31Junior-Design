#include <Arduino.h>
#include "ambient_light.h"

const float ADC_RESOLUTION = 5.0 / 1023.0; 

bool daytime() {
    // raw adc val
    int adc = analogRead(photoresistor_pin); 

    float photo_voltage = adc * ADC_RESOLUTION;

    Serial.print("voltage: "); Serial.println(photo_voltage); 
    
    if (photo_voltage > 2.5) {
        return true; 
    }
    
    return false; 
}