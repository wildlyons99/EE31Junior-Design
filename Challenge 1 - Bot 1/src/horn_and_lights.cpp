/* 
 *
 */

#include <Arduino.h>
#include "horn_and_lights.h"

const int headlights = 1; 
const int brake = 2; 

const int right_blinker = 3; 
const int left_blinker = 4;  

void setup_horn() {
    pinMode(hornPin, OUTPUT);
}

void setup_lights() {
    pinMode(headlights, OUTPUT);
    pinMode(brake, OUTPUT);
    pinMode(right_blinker, OUTPUT);
    pinMode(left_blinker, OUTPUT);

    digitalWrite(left_blinker, LOW); 
    digitalWrite(right_blinker, LOW); 
    digitalWrite(brake, LOW); 
    digitalWrite(headlights, LOW); 

    // setup state LEDs
}

/* blink_left 
 * blinks the left LED while 
 */

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