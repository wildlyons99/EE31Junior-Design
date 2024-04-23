#include <Arduino.h>

const int hornPin = 4; // Output pin for the square wave
const int greenPin = 21; // Output pin for green LED
const int yellowPin = 20; // Output pin for yellow LED

const int redPin = 13;
const int bluePin = 12;

int ledArray[4] = {greenPin, yellowPin, redPin, bluePin};

void honk(); 

void setup() {
  pinMode(hornPin, OUTPUT);
  for (int i = 0; i < 2; i++) {
    honk();
  }
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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
}

void loop() {
  // don't look at this code for too long. terrors.
  for (int i = 0; i < 4; i++) {
    honk();

    if (i == 0) digitalWrite(greenPin, HIGH);
    else digitalWrite(greenPin, LOW);
    if (i == 1) digitalWrite(yellowPin, HIGH);
    else digitalWrite(yellowPin, LOW);
    if (i == 2) digitalWrite(redPin, HIGH);
    else digitalWrite(redPin, LOW);
    if (i == 3) digitalWrite(bluePin, HIGH);
    else digitalWrite(bluePin, LOW);

    delay(1000);
  }
}