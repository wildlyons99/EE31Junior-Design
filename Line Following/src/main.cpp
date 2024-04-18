// main.cpp
// Tom Lyons
// 
// EE31 Junior Design - phase 3A
// Better name would be sensor Network
// Tufts University 

// Arduino 
#include <Arduino.h>

// C std 
#include <stdbool.h>

// Our Component Files
#include "collision_detection.h"
#include "color_detection.h" 
#include "motors.h"
#include "ambient_light.h"
 
void setup() {
    // Initialialize Pins for Color Detection
    setup_color_detection(); 

    // Initialize Pins for Motor Stuff
    setup_motors(); 
    
    delay(3000); 
    Serial.begin(9600);
    Serial.print("beginning...\n"); 
}
 
void loop() {
    if (daytime()) {
        Serial.println("Its daytime!"); 
    } else {
        Serial.println("It is night.");
    }

    delay(1000); 
    
    // char *color_string[] = {"None", "Black", "Blue", "Yellow", "Red"}; 

    // enum colors color = detectColor();     

    // if (!obsticle()) {
    //     drive_forward(); // change so not setting pins each time?? 
    // } else {
    //     stop_all(); 
    // }
    // delay(1000); 



    // // Go forwards
    // go_forward(3000);

    // delay(1000); 
    
    // // Go right
    // turn_right(775);

    // delay(1000); 
    
    // // // Go left
    // turn_left(860);

    // delay(3000); 
}