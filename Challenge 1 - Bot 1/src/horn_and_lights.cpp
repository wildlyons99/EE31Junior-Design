/* 
 *
 */

#include <Arduino.h>
#include "horn_and_lights.h"

void setup_horn() {
    pinMode(hornPin, OUTPUT);; 
}

/* honk
 * Purpose: Plays a "honk" sound
 */ 
void honk() {
    for (int i = 0; i < 1202; i++) {
        digitalWrite(hornPin, HIGH); // Set the output pin HIGH
        delayMicroseconds(208); // Delay for half of the square wave period (208 us)
        digitalWrite(hornPin, LOW); // Set the output pin LOW
        delayMicroseconds(208); // Delay for half of the square wave period (208 us)
    }
    digitalWrite(hornPin, LOW);
    delay(100); 
}

void honk_times(int num_times) {
    for (int i = 0; i < num_times; i++) {
        honk(); 
        delay(100); 
    }
}