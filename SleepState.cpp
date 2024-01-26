#include <Arduino.h>

int brightness = 255;               // how bright the LED is
int fadeAmount = -10;               // how many points to fade the LED by
unsigned long previousMillis = 0UL; // Used as a reference point for "counting" ms
unsigned long interval = 1000UL;    // Used as a final reference point for "counting" ms
int four_choice = 0;                // Used to choose blinking or fading for "Sleep State"

void fade(int p, int time_delay, int &brightness, int &fadeAmount)
{
  // set the brightness of pin p:
  analogWrite(p, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255)
  {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
  delayMicroseconds(time_delay);
}

int timed = 1000; // in ms
void setup()
{
  // set pinout up for LED, just 1 pin
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void delayonetwofive()
{
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
  delayMicroseconds(12500);
}

void FourHzBlink()
{
  // First step of 4Hz (Sleep state) is to blink 4x over 1 second (thus the 125ms delays)
  if (four_choice == 0)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(10, HIGH);
      delayonetwofive();
      digitalWrite(10, LOW);
      delayonetwofive();
    }

    four_choice = 1;
  }
  else
  {
    // Once the 4Hz blinking is done, Fade out over ~1 second.
    // Have to reset brightness and fadeAmount each time to always start at full brightness and fade out.
    fade(10, 3000, brightness, fadeAmount);
    if (brightness <= 0)
    {
      brightness = 255;
      fadeAmount = -10;
      four_choice = 0;
    }
  }
}

int num = 15;
void loop()
{
  // // digitalWrite(11, LOW);
  // digitalWrite(12, LOW);
  // digitalWrite(13, LOW);
  // delay(timed);
  // // digitalWrite(11, HIGH);
  // digitalWrite(12, HIGH);
  // digitalWrite(13, HIGH);
  // delay(timed);

  // fade(10, 30, brightness, fadeAmount);
  FourHzBlink();
}