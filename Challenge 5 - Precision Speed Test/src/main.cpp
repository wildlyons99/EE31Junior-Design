#include <Arduino.h>

#include "motors.h"

void setup() {
    setup_motors(); 

    delay(3000); 
}


void loop() {
    unsigned int now = millis(); 

    while (millis() - now <= 20000) {
        go_forward(150); 

        delay(75); 
    }

    while(1); 
}
