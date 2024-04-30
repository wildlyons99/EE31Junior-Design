// Arduino Lib
#include <Arduino.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"

const int turn_right_180 = 1050; 

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
        
    // // drive pretty much straigh to the wall until detects collision
    // drive_forward(); 

    // // keep driving until collision detected
    // while(!obsticle())
    //     delay(100); 
    
    // // then stop
    // stop_all(); 

    // Serial.println("Obsticle"); 

    // delay(1000); 

    // // turn around and go back until find the red line
    // turn_left(turn_right_180); 

    // drive_forward(); 
    
    // while(detectColor() != Red); 
    // stop_all(); 

    // follow_line(Red); 

    // turn_left(turn_right_180 / 2); 

    // // drive forward until get to yellow line
    // drive_forward(); 
    // while(detectColor() != Yellow); 
    // stop_all(); 

    // follow_line(Yellow); 


    // // turn_left()
    // Serial.println("done"); 

    // // while(1); 

    // turn_left(turn_right_180 / 2); 

    // drive_forward(); 
    // while(!obsticle())
    //     delay(100); 

    // stop_all(); 

    // turn_left(turn_right_180); 

    // while(1); 
}
