/* follow_line.cpp
 * Tom Lyons
 * Code for following a given line
 */

// define arrduino Lib
#include <Arduino.h>

// Header File
#include "follow_line.h"

// Local Helper Files 
#include "collision_detection.h"
#include "color_detection.h"
#include "motors.h"

// update values accordingly
const int turn_speed = 80; 

/* follow line
 * Purpose:   
 *      follow a line
 * Arguments: 
 *      (enum colors) - the color to finish
 * Notes:     
 *  - Follows the left edge of the line
 *  - Begins with a left turn
 */
void follow_line(enum colors color) {
    turn_right(400); 
    
    while (!obsticle()) {
        if (detectColor() == color) {
            // pivot right
            analogWrite(motorA1, LOW); // a is right motor
            analogWrite(motorA2, LOW);
            analogWrite(motorB1, turn_speed);
            analogWrite(motorB2, LOW);
            //delay(50); 
            // delay(100); 
            // stop_all(); 
        } else {
            // pivot_left
            analogWrite(motorA1, LOW); // a is right motor
            analogWrite(motorA2, turn_speed);
            analogWrite(motorB1, LOW);
            analogWrite(motorB2, LOW);
            
            //delay(50); 
            // delay(100); 
            // stop_all(); 
        }
        delay(10); 
    }
    stop_all(); 
}

