#include <Arduino.h>

#include "motors.h"
#include "pins.h"
#include "light_comm.h"

void setup() {
  // put your setup code here, to run once:
  setup_motors();
  Pins pinobject;
  pinobject.setPins();
  Serial.begin(9600);
  delay(3000);
}

/* Challenge 2 Requirements
  Communicate with other bot (NOT DONE HERE AS OF 4/28/24)
  Move forwards 12in
  Stop
  turn 180 deg
  Stop
  move backwards 3in
  Stop
  turn left
  turn right
  turn right
*/
Light_Comm lightcomm;
void loop() {
  // lightcomm.chall1_receive();
    unsigned int now = millis(); 

    while (millis() - now <= 9800) { // Move forwards 12 inches
        go_forward(110); 

        delay(100); 
    }

    delay(1000); // Stop

    turn_right(1100); // Turn 180 deg right

    delay(1000); // Stop

    now = millis();
    while (millis() - now <= 3900) { // Move backwards 3 inches
        go_backwards(110); 

        delay(100); 
    }

    delay(1000); // Stop

    turn_left(590); // Turn 90 deg left

    for (int i = 0; i < 2; i++) {
      delay(250); // rest

      turn_right(580); // Turn 90 deg right
    }

    delay(250); // rest
    turn_right(575); // Turn 90 deg right

    now = millis();
    while (millis() - now <= 14100) { // Move backwards ~15 inches
        go_backwards(110); 

        delay(100); 
    }

    while(1); 
}
