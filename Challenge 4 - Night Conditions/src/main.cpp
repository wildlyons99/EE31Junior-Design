#include <Arduino.h>

#include "motors.h"
#include "photoresistor.h"
#include "collision_detection.h"
#include "horn_and_lights.h"
#include "motors.h"
#include "pins.h"
#include "light_comm.h"

void setup()
{
    setup_motors();
    setup_lights();
    Pins pinobject;
    pinobject.setPins();
    Serial.begin(9600);

    delay(3000);
}

Light_Comm lightcomm;
void loop()
{
    // lightcomm.chall1_receive();
    // obsticle();
    // delay(300);
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
        delay(5000);
        while(1);
    }
}
