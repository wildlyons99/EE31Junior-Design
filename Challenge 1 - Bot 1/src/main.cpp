// Arduino Lib
#include <Arduino.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"

const int turn_right_180 = 1050;

void setup()
{
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

void loop()
{
    detectColor();

    delay(750);

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

    while (detectColor() != Red)
        ;
    stop_all();

    // Once bot comes back and finds the red line, blink red light
    digitalWrite(redStatus, HIGH);

    follow_line(Red);

    // After stopping at wall, THEN
    BlinkRedStatus();
    BlinkRedStatus();
    BlinkRedStatus();
    digitalWrite(greenStatus, HIGH);

    // Communicate with BOT 2, THEN
    // Once our bot receives message back, THEN
    headAndRear();
    honk_times(2);

    turn_left(turn_right_180 / 2);

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

    // turn_left()
    Serial.println("done");

    // while(1);

    turn_left(turn_right_180 / 2);

    drive_forward();
    while (!obsticle())
        delay(100);

    stop_all();

    turn_left(turn_right_180);

    while (1)
        ;
}
