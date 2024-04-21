/*
 * light_comm.cpp
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 4/4/2024
 *
 */

#include "light_comm.h"
#include <Arduino.h>
#include "pins.h"
#include "utils.h"

const int Light_Comm::threshold = 150;


/*
 * Purpose: Send High-Low-High-Low signal as specified for Challenge 1
 */
void Light_Comm::chall1_send() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 753; j++) {
      // Generate a high-amplitude square wave with f = 3kHz
      analogWrite(Pins::commLED, HIGH); // Set the output pin HIGH to represent an AM signal with a higher peak
      delayMicroseconds(166); // Delay for half the period (1/2 * 1/3000 seconds = 166.67 microseconds)
      analogWrite(Pins::commLED, LOW); // Set the output pin LOW
      delayMicroseconds(166); // Delay for the other half of the period    
    }
    for (int i = 0; i < 753; i++) {
      // Generate a low-amplitude square wave with f = 3kHz
      analogWrite(Pins::commLED, 90); // Set the output pin to 90 to represent an AM signal with a lower peak
      delayMicroseconds(166); // Delay for half the period (1/2 * 1/3000 seconds = 166.67 microseconds)
      analogWrite(Pins::commLED, LOW); // Set the output pin LOW
      delayMicroseconds(166); // Delay for the other half of the period
    }
  }
}

/*
 * Purpose: Send High-Low-High-Low signal as specified for Challenge 1
 */
void Light_Comm::chall1_receive() {
  while (analogRead(Pins::commIn) < threshold) {}
  delay(250);

  if (analogRead(Pins::commIn) < threshold) {
    Serial.println("Warning: Signal detected is not of proper format (low 1 not detected)");
    return;
  }
  delay(250);

  if (analogRead(Pins::commIn) < threshold) {
    Serial.println("Warning: Signal detected is not of proper format (high 2 not detected)");
    return;
  }
  delay(250);

  if (analogRead(Pins::commIn) < threshold) {
    Serial.println("Warning: Signal detected is not of proper format (low 2 not detected)");
    return;
  }

  Serial.println("Message received!");
  chall1_msg_received();
}

/*
 * Purpose: Flash headlights, brake lights, and honk horn twice.
 * Note: Loop is 'unrolled' to maintain 50% duty cycle
 */
void Light_Comm::chal1_msg_received() {
  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, HIGH);
  digitalWrite(Pins::horn, HIGH);
  delay(150);

  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::horn, LOW);
  delay(150);

  digitalWrite(Pins::headlights, HIGH);
  digitalWrite(Pins::brakelights, HIGH);
  digitalWrite(Pins::horn, HIGH);
  delay(150);

  digitalWrite(Pins::headlights, LOW);
  digitalWrite(Pins::brakelights, LOW);
  digitalWrite(Pins::horn, LOW);
  delay(150);
}
