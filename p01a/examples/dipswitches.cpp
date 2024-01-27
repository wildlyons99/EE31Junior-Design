#include <Arduino.h>

const byte redPin   = 9;
const byte greenPin = 6;
const byte bluePin  = 10;

const byte dip1 = 2;
const byte dip2 = 3;
const byte dip3 = 4;
const byte dip4 = 5;

volatile byte redstate      = HIGH;
volatile byte greenstate    = HIGH;
volatile byte bluestate     = HIGH;


void redblink() {
    redstate = !redstate;
}

void greenblink() {
    greenstate = !greenstate;
}

void blueblink() {
    bluestate = !bluestate;
}

void setup() {
    pinMode(dip1, INPUT_PULLUP);
    pinMode(dip2, INPUT_PULLUP);
    pinMode(dip3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(dip1), redblink, CHANGE);
    attachInterrupt(digitalPinToInterrupt(dip2), greenblink, CHANGE);
    attachInterrupt(digitalPinToInterrupt(dip3), blueblink, CHANGE);
}

void loop() {
    volatile int redvalue = redstate ? 0 : 255;
    volatile int greenvalue = greenstate ? 0 : 255;
    volatile int bluevalue = bluestate ? 0 : 255;
    analogWrite(redPin, redvalue);          // Using analogWrite for PWM pin?
    analogWrite(greenPin, greenvalue);
    analogWrite(bluePin, bluevalue);

}
