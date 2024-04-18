#include <Arduino.h>

const int hornPin = 4; // Output pin for the square wave

void honk(); 

void setup() {
  pinMode(hornPin, OUTPUT);
  for (int i = 0; i < 2; i++) {
    honk();
  }
}

void loop() {
  
}

// honks twice
void honk() {
    for (int i = 0; i < 1202; i++) {
        digitalWrite(hornPin, HIGH); // Set the output pin HIGH
        delayMicroseconds(208); // Delay for half of the square wave period (208 us)
        digitalWrite(hornPin, LOW); // Set the output pin LOW
        delayMicroseconds(208); // Delay for half of the square wave period (208 us)
    }
    digitalWrite(hornPin, LOW);
    delay(100); 
}