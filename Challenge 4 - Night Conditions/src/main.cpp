#include <Arduino.h>

#include "motors.h"
#include "photoresistor.h"
#include "collision_detection.h"
#include "horn_and_lights.h"

void setup()
{
    setup_motors();
    setup_lights();
    Serial.begin(9600);

    delay(3000);
}

void loop()
{
    go_forward(50);
    if (obsticle())
    {
        stop_all();
        delay(300);
        morse_hi();
        delay(300);
        flash_headlights();
        delay(300);
        rear_turn_signal();
        while (1)
        {
        }
    }
}
