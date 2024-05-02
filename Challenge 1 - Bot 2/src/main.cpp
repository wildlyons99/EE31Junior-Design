/////////////////////////////////////////////////////////
///////                  BOT 2                     ////// 
/////////////////////////////////////////////////////////

// Arduino Lib
#include <Arduino.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"
#include "wifi_comm.h"

const int turn_right_180 = 1050;

void setup()
{
    setup_motors();
    setup_color_detection();
    setup_horn();
    setup_lights();

    Serial.begin(9600);

    delay(2000);
}

void loop()
{
    // wait for light based comm message

    // After bot 2 recieves message 
    // Bot 2 flashes its headlights, flashes brake lights, and beeps horn twice
    for (int i = 0; i < 2; i++) {
        digitalWrite(headlights, HIGH); 
        digitalWrite(brake, HIGH); 
        honk(); 
        delay(200); 
        digitalWrite(headlights, LOW); 
        digitalWrite(brake, LOW); 
        delay(200); 
    }

    // send same light message back to bot 1

    // after sending message, wait 5 seconds
    delay(5000);


}
