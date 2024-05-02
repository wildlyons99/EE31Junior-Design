/*****************************************************************
 *                      COLOR LINE DETECTION CODE                *
 *****************************************************************/

#include <Arduino.h>
#include <color_detection.h>


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
    // static unsigned long previousMillis = 0;
    // unsigned long currentMillis = millis();

    // if(currentMillis - previousMillis >= blueRedFreq) {

    char *color_string[] = {"None", "Black", "Blue", "Yellow", "Red"}; 

    // Serial.print("Color Detected: "); Serial.println(color_string[currColor]); 

    //blue is high, red is low
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);

    delay(50);

    //read blue value
    blueValue = analogRead(colorRead);
    blueValue = blueValue / 1023 * 5;


    //blue is low, red is high
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);

    delay(50);
    
    //read red value
    redValue = analogRead(colorRead);
    redValue = redValue / 1023 * 5;

    // turn both leds off
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
        

    // Serial.print("Analog Red: "); Serial.print(redValue); 
    // Serial.print("                   Analog Blue: "); Serial.println(blueValue); 

    if(redValue < 1.6 && blueValue < 1.5){
        currColor = Black;
        // Serial.println("BLACK");
    } else if(redValue >= 1.6 && redValue < 3 && blueValue >= 1.6 && blueValue <= 3){
        currColor = Blue;
        // Serial.println("BLUE");
    } else if(redValue >= 3 && redValue < 4.5 && blueValue >= 2.5 && blueValue <= 4.5){
        currColor = Yellow;
        // Serial.println("YELLOW");
    } else if(redValue >= 3 && redValue <= 4 && blueValue >= 0.5 && blueValue <= 1.6){
        currColor = Red;
        // Serial.println("RED");
    } else {
        currColor = None;
        // Serial.println("NONE");
    }

    // values before new battery
    /*
    if(redValue < 1.6 && blueValue < 1.5){
        currColor = Black;
        // Serial.println("BLACK");
    } else if(redValue >= 1.6 && redValue <= 3 && blueValue >= 2.2 && blueValue <= 3){
        currColor = Blue;
        // Serial.println("BLUE");
    } else if(redValue >= 3 && redValue < 4.5 && blueValue >= 2.5 && blueValue <= 4.5){
        currColor = Yellow;
        // Serial.println("YELLOW");
    } else if(redValue >= 3 && redValue <= 4 && blueValue >= 1.4 && blueValue <= 2.2){
        currColor = Red;
        // Serial.println("RED");
    } else {
        currColor = None;
        // Serial.println("NONE");
    }
     */

    return currColor;
}