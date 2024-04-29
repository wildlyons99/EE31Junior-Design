// Arduino Lib
#include <Arduino.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"

const int turn_right_180 = 1300; 


void setup() {
    setup_motors(); 
    setup_color_detection();
    setup_horn(); 
    setup_lights(); 

    // // for collision detection power wire 
    // pinMode(collision_power, OUTPUT);
    // digitalWrite(collision_power, HIGH); 
    Serial.begin(9600); 

    delay(2000); 
}

void loop() {
    detectColor(); 

    delay(750); 
    
    // follow_line(Red);
    
    // // drive pretty much straigh to the wall until detects collision
    // drive_forward(); 

    // // keep driving until collision detected
    // while(!obsticle())
    //     delay(100); 
    
    // // then stop
    // stop_all(); 

    // Serial.println("Obsticle"); 

    // delay(2000); 

    // // turn around and go back until find the red line
    // turn_right(turn_right_180); 

    // drive_forward(); 
    
    // while(detectColor() != Red); 
    // stop_all(); 

    // while(1); 

    // follow red line -> turn left and go until detect collision on wall
    // follow_

    // turn left and go to yellow line

    // turn left to follow yellow line all the way 

    // until about 6 inches away left go left and stop 
}
