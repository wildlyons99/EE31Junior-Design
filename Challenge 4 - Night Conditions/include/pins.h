/*
 * pins.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#ifndef __PINS_H__
#define __PINS_H__

#include <Arduino.h>

class Pins {
public:
  // PWM motor pins for variable speed, turning
  const static int motor1;
  const static int motor2;
  const static int motor3;
  const static int motor4;

  // Color detection system for path following
  const static int colorIn;

  // IR detection system for collision
  const static int collisionIn;

  // IR detection system for communication
  const static int commLED;
  const static int commIn;

  // Battery management system
  const static int batteryMgmtLED;
  const static int batteryMgmtIn;

  // Indicators
  const static int headlights;
  const static int brakelights;
  const static int leftTurnSignal;
  const static int rightTurnSignal;
  const static int redStateLED;
  const static int blueStateLED;
  const static int greenStateLED;
  const static int yellowStateLED;
  const static int horn;

  void setPins();
};

#endif