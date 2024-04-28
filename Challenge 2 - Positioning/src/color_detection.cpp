/*****************************************************************
 *                      COLOR LINE DETECTION CODE                *
 *****************************************************************/

#include <Arduino.h>
#include <color_detection.h>

const int blueRedFreq = 50;

// Pin Values
int redLED = 3;
int blueLED = 2;
#define colorRead A3

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

    if(currentMillis - previousMillis >= blueRedFreq) {

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

    Serial.print("Analog Red: "); Serial.print(redValue); 
    Serial.print("                   Analog Blue: "); Serial.println(blueValue); 


    if(redValue < 1.6 && blueValue < 1.5){
        currColor = Black;
        // Serial.println("BLACK");
    } else if(redValue > 1.6 && redValue < 3 && blueValue > 2.2 && blueValue < 3){
        currColor = Blue;
        // Serial.println("BLUE");
    } else if(redValue > 3 && redValue < 4.5 && blueValue > 2.5 && blueValue < 4.5){
        currColor = Yellow;
        // Serial.println("YELLOW");
    } else if(redValue > 3 && redValue < 4 && blueValue > 1.5 && blueValue < 2.2){
        currColor = Red;
        // Serial.println("RED");
    } else {
        currColor = None;
        // Serial.println("NONE");
    }

    return currColor;
}