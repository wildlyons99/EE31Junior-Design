#include <Arduino.h>

#include "motors.h"
#include "photoresistor.h"
#include "collision_detection.h"
#include "horn_and_lights.h"

void setup()
{
    setup_motors();
    setup_lights();

    delay(3000);
}

void loop()
{
    if (obsticle())
    {
        stop_all();
        // delay(100);
        // IR_Morse_hi();
        delay(100);
        flash_headlights();
        delay(100);
        rear_turn_signal();
    }
}
