// Tom's proof of concept code
#include <arduino.h>

int brightness; 
void setup()
{
  pinMode(10, OUTPUT);
  // attachInterrupt(digitalPinToInterrupt(A0), pot_check, CHANGE);
  digitalWrite(10, HIGH); 
  delay(500); 
  digitalWrite(10, LOW); 
  
  Serial.begin(9600); 
  while (!Serial); 
  
  Serial.print("hello"); 
  delay(2000); 
  
  brightness = 250; // init_brightness
}

void loop()
{
    // int intermediate_delay_ms = (6 * 1000) / 100; 
  
    //int fade_amount = brightness / 50; 
    // 5000ms 
    Serial.print("testing fade"); 
  	for (int i = 0; i < 50; i++) {
        // set the brightness of pin 9:
        analogWrite(10, brightness);

        // change the brightness for next time through the loop:
        brightness = brightness - 5;

        // wait to see the dimming effect
        delay(100);
    }
    
    analogWrite(10, 0);
  
  Serial.print("Done testing\n"); 
  
  while(true); // hold here
}