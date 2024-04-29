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

void follow_line(enum colors color) {
    while (!obsticle()) {
        go_forward(250); 
        
        delay(250); 

        // check that still on the line
        if (detectColor() != color) {
            int iteration = 1; 

            turn_right(100);

            delay(250); 

            while (detectColor() != color) {
                turn_left(100 * iteration * 2); 

                delay(250); 

                if (detectColor() == color) {
                    return;
                }

                delay(250); 

                turn_right(100 * iteration++ * 2); 
            }
        }
    }    
}

