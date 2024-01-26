#include <Arduino.h>

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

void fade(int p, int total_ms_delay, int &brightness, int &fadeAmount) {
    // set the brightness of pin p:
    analogWrite(p, brightness);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for time_delay/255 milliseconds to see the dimming effect
    delay(total_ms_delay*2/255);
}

void blink(int p, int hz) {
    digitalWrite(p, HIGH);
    delay(1 / (float) hz * 1000); // delay is in ms, and hz is 1/s
    digitalWrite(p, LOW);
    delay(1 / (float) hz * 1000); // delay is in ms, and hz is 1/s
}

int timed = 1000; // in ms
int red     = 9;
int green   = 6;
int blue    = 10;

const byte dip1 = 2;
const byte dip2 = 3;
const byte dip3 = 4;
const byte dip4 = 5;

volatile byte state = LOW;

void setup() {
    // set pinout up for LED, just 1 pin
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(dip1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(dip1), pin_ISR, CHANGE);
}

int num = 5;
void loop() {
    // fade(red, 6000, brightness, num);
    // // fade(green, 6000, brightness, num);
    // fade(blue, 6000, brightness, num);
    
    // blink(green, 4);
}

void pin_ISR() {
    state = digitalRead(dip1);
    digitalWrite(green, state);
}