/*
 * drive.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include <Arduino.h>

#include "drive.h"
#include "pins.h"
#include "utils.h"

void Drive::forward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 155);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
}

void Drive::backward() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 155);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 155);
}

// TODO: Values might require tuning
void Drive::leftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 80);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::leftSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::leftTurnSignal, HIGH);
  analogWrite(Pins::motor1, 130);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 155);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::leftTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::rightSoftCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 155);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 130);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}

// TODO: Values might require tuning
void Drive::rightCurveTurn() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::rightTurnSignal, HIGH);
  analogWrite(Pins::motor1, 155);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 80);
  analogWrite(Pins::motor4, 0);
  digitalWrite(Pins::rightTurnSignal, LOW);
}

void Drive::stop() {
        digitalWrite(Pins::headlights, LOW);
        digitalWrite(Pins::brakelights, HIGH);
        analogWrite(Pins::motor1, 0);
        analogWrite(Pins::motor2, 0);
        analogWrite(Pins::motor3, 0);
        analogWrite(Pins::motor4, 0);
}

// TODO: Values might require tuning
void Drive::leftFollowLine(color c) {
  while (not collision_detected()) {
    drive.leftPointTurn(15);
    drive.rightCurveTurn();
    while ((not collision_detected()) and (getColor() != c))
      millisDelay(10);
  }
  drive.stop();
}

// TODO: Values might require tuning
void Drive::rightFollowLine(color c) {
  while (not collision_detected()) {
    drive.rightPointTurn(15);
    drive.leftCurveTurn();
    while ((not collision_detected()) and (getColor() != c))
      millisDelay(10);
  }
  drive.stop();
}

void Drive::forwardToWall() {
  drive.forward();
  while (not collision_detected())
    millisDelay(10);
  drive.stop();
}

void Drive::forwardToColor(color c) {
  drive.forward();
  while (getColor() != c)
    millisDelay(10);
  drive.stop();
}

void Drive::forwardFor(int time) {
        digitalWrite(Pins::headlights, HIGH);
        digitalWrite(Pins::brakelights, LOW);
        analogWrite(Pins::motor1, 155);
        analogWrite(Pins::motor2, 0);
        analogWrite(Pins::motor3, 155);
        analogWrite(Pins::motor4, 0);
        millisDelay(time);
}

void Drive::backwardFor(int time) {
        digitalWrite(Pins::headlights, HIGH);
        digitalWrite(Pins::brakelights, LOW);
        analogWrite(Pins::motor1, 0);
        analogWrite(Pins::motor2, 155);
        analogWrite(Pins::motor3, 0);
        analogWrite(Pins::motor4, 155);
        millisDelay(time);
}

//Found that delay of 900 is 90 degrees
void Drive::leftPointTurn(unsigned long degrees) {
        digitalWrite(Pins::headlights, HIGH);
        digitalWrite(Pins::brakelights, LOW);
        digitalWrite(Pins::leftTurnSignal, HIGH);

        unsigned long time = (degrees * 910)/90;
        //int time = math / 90;
        analogWrite(Pins::motor1, 0);
        analogWrite(Pins::motor2, 130);
        analogWrite(Pins::motor3, 130);
        analogWrite(Pins::motor4, 0);

        millisDelay(time);

        digitalWrite(Pins::leftTurnSignal, LOW);
        stopFor(10);
}

//NOTE : For some reason the right wheel does not like to go backwards
// for values less than 130 idk why
//Found that delay of 750 is 90 degreees
void Drive::rightPointTurn(unsigned long degrees) {
        digitalWrite(Pins::headlights, HIGH);
        digitalWrite(Pins::brakelights, LOW);
        digitalWrite(Pins::rightTurnSignal, HIGH);

        unsigned long time = (degrees * 740)/90;
        //int time = time / 90;
        analogWrite(Pins::motor1, 130);
        analogWrite(Pins::motor2, 0);
        analogWrite(Pins::motor3, 0);
        analogWrite(Pins::motor4, 130);

        millisDelay(time);

        digitalWrite(Pins::rightTurnSignal, LOW);
        stopFor(10);
}

void Drive::stopFor(int time) {
  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, HIGH);
  analogWrite(Pins::motor1, 0);
  analogWrite(Pins::motor2, 0);
  analogWrite(Pins::motor3, 0);
  analogWrite(Pins::motor4, 0);
  millisDelay(time);
}
