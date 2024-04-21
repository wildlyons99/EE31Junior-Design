/*
 * EE31_Phase2B.ino
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#include "drive.h"
#include "pins.h"

Drive drive;
Pins pins;

void setup() {
  pins.setPins();
}

void loop() {
  drive.forward(1000);
}
