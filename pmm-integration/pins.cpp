/*
 * pins.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#include "pins.h"
#include <Arduino.h>

// PWM motor pins for variable speed, turning
const int Pins::motor1 = 6;
const int Pins::motor2 = 5;
const int Pins::motor3 = 10;
const int Pins::motor4 = 11;

// Color detection system for path following
const int Pins::redSensorLED = 7;
const int Pins::blueSensorLED = 8;
const int Pins::colorIn = A4;

// IR detection system for collision
const int Pins::collisionLED = 3;
const int Pins::collisionIn = A0;

// IR detection system for collision
const int Pins::commLED = 3;
const int Pins::commIn = A0;

// Indicators
const int Pins::headlights = 4;
const int Pins::brakelights = 9;
const int Pins::redStateLED = 13;
const int Pins::blueStateLED = 12;
const int Pins::horn = 15;


void Pins::setPins(bool detect_collisions=true) {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  pinMode(redSensorLED, OUTPUT);
  pinMode(blueSensorLED, OUTPUT);
  pinMode(colorIn, INPUT);

  pinMode(collisionLED, OUTPUT);
  pinMode(collisionIn, INPUT);

  pinMode(commLED, OUTPUT);
  pinMode(commIn, INPUT);

  pinMode(headlights, OUTPUT);
  pinMode(brakelights, OUTPUT);
  pinMode(redStateLED, OUTPUT);
  pinMode(blueStateLED, OUTPUT);
  pinMode(horn, OUTPUT);

  if (detect_collisions) {
    digitalWrite(irLED, HIGH);
  }
}
