/*
 *
 */

#include <Arduino.h>
#include "horn_and_lights.h"
#include "pins.h"

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
    pinMode(ir, OUTPUT);
    pinMode(redStatus, OUTPUT);
    pinMode(greenStatus, OUTPUT);
    pinMode(blueStatus, OUTPUT);
    pinMode(yellowStatus, OUTPUT);

    digitalWrite(left_blinker, LOW);
    digitalWrite(right_blinker, LOW);
    digitalWrite(brake, LOW);
    digitalWrite(headlights, LOW);
    digitalWrite(ir, LOW);
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
    delay(200);
    digitalWrite(headlights, LOW);
    delay(200);
    digitalWrite(headlights, HIGH);
    delay(200);
    digitalWrite(headlights, LOW);
    delay(200);
}

/* rear_turn_signal
Illuminate rear yellow turn signals. (USED FOR CHALLENGE 4)
*/
void rear_turn_signal()
{
    digitalWrite(right_blinker, HIGH);
    digitalWrite(left_blinker, HIGH);
    delay(200);
    digitalWrite(right_blinker, LOW);
    digitalWrite(left_blinker, LOW);
    delay(200);
    digitalWrite(right_blinker, HIGH);
    digitalWrite(left_blinker, HIGH);
    delay(200);
    digitalWrite(right_blinker, LOW);
    digitalWrite(left_blinker, LOW);
}

/*
    * headAndRear
    * Purpose: Flash headlights and rear turn signals

*/
void headAndRear()
{
    digitalWrite(headlights, HIGH);
    digitalWrite(right_blinker, HIGH);
    digitalWrite(left_blinker, HIGH);
    delay(200);
    digitalWrite(headlights, LOW);
    digitalWrite(right_blinker, LOW);
    digitalWrite(left_blinker, LOW);
    delay(200);
    digitalWrite(headlights, HIGH);
    digitalWrite(right_blinker, HIGH);
    digitalWrite(left_blinker, HIGH);
    delay(200);
    digitalWrite(headlights, LOW);
    digitalWrite(right_blinker, LOW);
    digitalWrite(left_blinker, LOW);
}

void morse_hi()
{
    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);
    delay(100);

    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);
    delay(100);

    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);
    delay(100);

    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);

    delay(300);

    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);
    delay(100);

    digitalWrite(ir, HIGH);
    delay(100);
    digitalWrite(ir, LOW);
    delay(100);
}

void BlinkRedStatus()
{
    digitalWrite(redStatus, HIGH);
    delay(100);
    digitalWrite(redStatus, LOW);
    delay(100);
}

void BlinkGreenStatus()
{
    digitalWrite(greenStatus, HIGH);
    delay(100);
    digitalWrite(greenStatus, LOW);
    delay(100);
}

void BlinkBlueStatus()
{
    digitalWrite(blueStatus, HIGH);
    delay(100);
    digitalWrite(blueStatus, LOW);
    delay(100);
}

void BlinkYellowStatus()
{
    digitalWrite(yellowStatus, HIGH);
    delay(100);
    digitalWrite(yellowStatus, LOW);
    delay(100);
}