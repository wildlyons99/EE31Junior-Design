/*
 * utils.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 3/4/2024
 *
 */

#include "utils.h"
#include <Arduino.h>

void millisDelay( long int delayTime){
  long int start_time = millis();
  while ( millis() - start_time < delayTime) ;
}