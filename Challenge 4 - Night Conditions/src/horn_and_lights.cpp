/*
 *
 */

#include <Arduino.h>
#include "horn_and_lights.h"

const int headlights = 1;
const int brake = 2;

const int right_blinker = 3;
const int left_blinker = 4;

void setup_horn()
{
    pinMode(hornPin, OUTPUT);
}

void setup_lights()
{
    pinMode(headlights, OUTPUT);
    pinMode(brake, OUTPUT);
    pinMode(right_blinker, OUTPUT);
    pinMode(left_blinker, OUTPUT);

    digitalWrite(left_blinker, LOW);
    digitalWrite(right_blinker, LOW);
    digitalWrite(brake, LOW);
    digitalWrite(headlights, LOW);
}

/* blink_left
 * blinks the left LED while
 */

/* honk
 * Purpose: Plays a "honk" sound
 */
void honk()
{
    for (int i = 0; i < 1202; i++)
    {
        digitalWrite(hornPin, HIGH); // Set the output pin HIGH
        delayMicroseconds(208);      // Delay for half of the square wave period (208 us)
        digitalWrite(hornPin, LOW);  // Set the output pin LOW
        delayMicroseconds(208);      // Delay for half of the square wave period (208 us)
    }
    digitalWrite(hornPin, LOW);
    delay(100);
}

void honk_times(int num_times)
{
    for (int i = 0; i < num_times; i++)
    {
        honk();
        delay(100);
    }
}

/* flash_headlights
Flash headlights twice (USED FOR CHALLENGE 4)
*/
void flash_headlights()
{
    digitalWrite(headlights, HIGH);
    delay(100);
    digitalWrite(headlights, LOW);
    delay(100);
    digitalWrite(headlights, HIGH);
    delay(100);
    digitalWrite(headlights, LOW);
    delay(100);
}

/* rear_turn_signal
Illuminate rear yellow turn signals. (USED FOR CHALLENGE 4)
*/
void rear_turn_signal()
{
    digitalWrite(right_blinker, HIGH);
    digitalWrite(left_blinker, HIGH);
    delay(500);
    digitalWrite(right_blinker, LOW);
    digitalWrite(left_blinker, LOW);
}