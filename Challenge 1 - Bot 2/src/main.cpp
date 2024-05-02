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

    wifi_connect(); 

    Serial.println("Connected!"); 

    // flash blue and red LEDs three times - successfully diagnostics
    for (int i = 0; i < 3; i++) {
        digitalWrite(blueStatus, HIGH); 
        digitalWrite(redStatus, HIGH); 
        delay(200); 
        digitalWrite(blueStatus, LOW); 
        digitalWrite(redStatus, LOW); 
        delay(200); 
    }

    delay(1000);
}

void loop()
{
    // a config feature for if we need to reconfigure sensor values
    detectColor();
    delay(750);

    // begin challenge 1
    // drive pretty much straigh to the wall until detects collision
    drive_forward();

    // keep driving until collision detected
    while (!obsticle())
        delay(100);

    // then stop
    stop_all();

    Serial.println("Obsticle");

    delay(1000);

    // turn around and go back until find the red line
    turn_left(turn_right_180);

    drive_forward();

    while (detectColor() != Blue)
        ;
    stop_all();

    // Once bot comes back and finds the red line, blink red light
    digitalWrite(redStatus, HIGH);

    // TRANSMIT LIGHT MESSAGE??? // or pretend while sending wifi 

    // After recieve message twice
    // Bot 1 flashes its headlights and brake lights twice  and beeps its horn twice
    for (int i = 0; i < 2; i++) {
        digitalWrite(headlights, HIGH); 
        digitalWrite(brake, HIGH); 
        honk(); 
        delay(200); 
        digitalWrite(headlights, LOW); 
        digitalWrite(brake, LOW); 
        delay(200); 
    }

    follow_line(Blue);

    // After stopping at wall, THEN
    digitalWrite(redStatus, LOW); // set LED low to allow for blinking
    delay(50); 
    BlinkRedStatus();

    // blinks its red LED and signals Bot 2. Bot 2 upon  receipt blinks its red LED.
    // Bot 2 signals back to Bot 1, Bot 1 blinks its red LED three  times, turns off the red LED and illuminates a green LED. 

    
    // blinks its red LED and signals Bot 2. 
    // Bot 2 signals back to Bot 1, Bot 1 blinks its red LED three  times, turns off the red LED and illuminates a green LED. 
    BlinkRedStatus(); // After recieving message back
    BlinkRedStatus();
    BlinkRedStatus();
    digitalWrite(greenStatus, HIGH);

    // Communicate with BOT 2, THEN
    // Once our bot receives message back, THEN
    headAndRear();
    honk_times(2);

    // go backwards
    go_backwards(500); 

    turn_right(turn_right_180 / 2);

    // drive forward until get to yellow line
    drive_forward();
    while (detectColor() != Yellow)
        ;
    stop_all();

    // After finding yellow, THEN
    honk_times(2);
    digitalWrite(greenStatus, LOW);
    delay(100);
    digitalWrite(yellowStatus, HIGH);

    follow_line(Yellow);

    // Tell bot 2 to continue

    // go backwards
    go_backwards(1000); 

    // turn_left()
    turn_right(turn_right_180 / 2);

    // drive back to wall
    drive_forward();
    while (!obsticle())
        delay(100);

    stop_all();

    turn_left(turn_right_180);

    // wait for bot 2 to finish
    while (1);
}
