#include <Arduino.h>

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

void fade(int p, int delay, int &brightness, int &fadeAmount) {
    // set the brightness of pin p:
    analogWrite(p, brightness);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(delay);
}

int timed = 1000; // in ms
void setup() {
    // set pinout up for LED, just 1 pin
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}

int num = 5;
void loop() {
    // // digitalWrite(11, LOW);
    // digitalWrite(12, LOW);
    // digitalWrite(13, LOW);
    // delay(timed);
    // // digitalWrite(11, HIGH);
    // digitalWrite(12, HIGH);
    // digitalWrite(13, HIGH);
    // delay(timed);

    fade(11, 30, brightness, num);
}