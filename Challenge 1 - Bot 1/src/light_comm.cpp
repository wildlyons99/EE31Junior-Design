/*
 * light_comm.cpp
 */

#include "light_comm.h"
#include <Arduino.h>
#include "pins.h"

const int threshold = 150;


/*
 * Purpose: Send High-Low-High-Low signal as specified for Challenge 1
 */
void chall1_send() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 753; j++) {
      // Generate a high-amplitude square wave with f = 3kHz
      analogWrite(ir, HIGH); // Set the output pin HIGH to represent an AM signal with a higher peak
      delayMicroseconds(166); // Delay for half the period (1/2 * 1/3000 seconds = 166.67 microseconds)
      analogWrite(ir, LOW); // Set the output pin LOW
      delayMicroseconds(166); // Delay for the other half of the period    
    }
    for (int i = 0; i < 753; i++) {
      // Generate a low-amplitude square wave with f = 3kHz
      analogWrite(ir, 90); // Set the output pin to 90 to represent an AM signal with a lower peak
      delayMicroseconds(166); // Delay for half the period (1/2 * 1/3000 seconds = 166.67 microseconds)
      analogWrite(ir, LOW); // Set the output pin LOW
      delayMicroseconds(166); // Delay for the other half of the period
    }
  }
}

/*
 * Purpose: Send High-Low-High-Low signal as specified for Challenge 1
 */
void chall1_receive() {
  while (analogRead(ir) < threshold) {}
  delay(250);

  if (analogRead(ir) < threshold) {
    Serial.println("Warning: Signal detected is not of proper format (low 1 not detected)");
    return;
  }
  delay(250);

  if (analogRead(ir) < threshold) {
    Serial.println("Warning: Signal detected is not of proper format (high 2 not detected)");
    return;
  }
  delay(250);

  if (analogRead(ir) < threshold) {
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
void chall1_msg_received() {
  digitalWrite(ir, HIGH);
  digitalWrite(ir, HIGH);
  digitalWrite(ir, HIGH);
  delay(150);

  digitalWrite(ir, LOW);
  digitalWrite(ir, LOW);
  digitalWrite(ir, LOW);
  delay(150);

  digitalWrite(ir, HIGH);
  digitalWrite(ir, HIGH);
  digitalWrite(ir, HIGH);
  delay(150);

  digitalWrite(ir, LOW);
  digitalWrite(ir, LOW);
  digitalWrite(ir, LOW);
  delay(150);
}