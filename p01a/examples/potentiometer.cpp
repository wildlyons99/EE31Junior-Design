#include <Arduino.h>

volatile int lightvalue = 0;
volatile int sensorvalue = 0;

void setup()
{
    pinMode(A0, INPUT_PULLUP);
    Serial.begin(9600); 
}

void loop()
{
    sensorvalue = analogRead(A0);
    lightvalue = map(sensorvalue, 0, 673, 0, 255);
    analogWrite(6, lightvalue);
    
    Serial.print(sensorvalue); Serial.print(" "); Serial.println(lightvalue);
}