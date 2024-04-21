/*
 * colors.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 4/8/2024
 *
 */

#include "colors.h"
#include <Arduino.h>
#include <string>
#include "pins.h"
#include "utils.h"

color getColor() {
  int blueIn, redIn;
  
  digitalWrite(Pins::redSensorLED, LOW);
  digitalWrite(Pins::blueSensorLED, HIGH);
  millisDelay(1);
  blueIn = analogRead(Pins::colorIn);

  digitalWrite(Pins::redSensorLED, HIGH);
  digitalWrite(Pins::blueSensorLED, LOW);
  millisDelay(1);
  redIn = analogRead(Pins::colorIn);

  if (blueIn > 750) {
    if (redIn > 750) {
      return yellow;
    } else {
      return blue;
    }
  } else if (redIn > 750) {
    return red;
  } else {
    return black;
  }
}

std::string colorToString(color toPrint) {
  switch (toPrint) {
    case red:
      return "red";
    case blue:
      return "blue";
    case yellow:
      return "yellow";
    case black:
      return "black";
  }
}
