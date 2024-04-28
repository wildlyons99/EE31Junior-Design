#include <Arduino.h>

#include "motors.h"

void setup() {
  // put your setup code here, to run once:
  setup_motors();
  
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
void loop() {
    unsigned int now = millis(); 

    // while (millis() - now <= 11250) { // Move forwards 12 inches
    //     go_forward(150); 

    //     delay(100); 
    // }

    // delay(1000); // Stop

    // turn_right(1012); // Turn 180 deg

    while (millis() - now <= 2250) { // Move backwards 3 inches
        go_forward(150); 

        delay(100); 
    }

    while(1); 
}
