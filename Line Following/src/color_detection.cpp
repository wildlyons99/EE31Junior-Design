/*****************************************************************
 *                      COLOR LINE DETECTION CODE                *
 *****************************************************************/

#include <Arduino.h>
#include <color_detection.h>

const int blueRedFreq = 50;

// Pin Values
int redLED = 3;
int blueLED = 2;
#define colorRead A2

float blueValue = 0.0;
float redValue = 0.0;
bool LEDstate; //0 = red, 1 = blue
enum colors currColor = None;

void setup_color_detection() {
    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    pinMode(colorRead, INPUT);
}

enum colors detectColor() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= blueRedFreq){

        // Serial.print("Red: ");
        // Serial.print(redValue);
        // Serial.print("        BLue: ");
        // Serial.println(blueValue);

        char *color_string[] = {"None", "Black", "Blue", "Yellow", "Red"}; 

        Serial.print("Color Detected: "); Serial.println(color_string[currColor]); 


    //reset count
    previousMillis = currentMillis; 
    LEDstate = !LEDstate;

    //flip LED
    if(LEDstate){
      //blue is high, red is low
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, HIGH);

            delay(20);

      //read blue value
      blueValue = analogRead(colorRead);
      blueValue = blueValue / 1023 * 5;

    } else {
      //blue is low, red is high
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, HIGH);

      delay(20);
      
      //read red value
      redValue = analogRead(colorRead);
      redValue = redValue / 1023 * 5;
    }
  }

  if(redValue < 1.6 && blueValue < 2.2){
    currColor = Black;
  } else if(redValue > 1.6 && redValue < 2.5 && blueValue > 2.2 && blueValue < 3){
    currColor = Blue;
  } else if(redValue > 2.5 && redValue < 4.5 && blueValue > 2.5 && blueValue < 3.5){
    currColor = Yellow;
  } else if(redValue > 2.5 && redValue < 4 && blueValue > 1.5 && blueValue < 2.2){
    currColor = Red;
  } else {
    currColor = None;
  }

  return currColor;
}