#include <Arduino.h>

const int redLED = 9;
const int blueLED = 10;
const int greenLED = 6;

int errorCode = 2;

// TODO set pins
const int switch1pin = 2;                 //pin for blueLED control for run state
const int switch2pin = 3;                 //pin for redLED control for run state
const int switch3pin = 4;                 //pin for run/sleep
const int switch4pin = 5;                 //pin for on/off switch


volatile bool blueRun = 0;                //blueLED @ 10Hz when high, else 1Hz
volatile bool redRun = 0;                 //redLED on when high, else off
volatile bool onOff = 0;                  //on when high
volatile bool runSleep = 0;               //run when high

// TODO set pins
const int potentiometer1pin = A0;
const int potentiometer2pin = A1;

int brightness = 255;            // how bright the LED is
int flashPattern = 0;

void switch1() {
    blueRun = !blueRun;
}

void switch2() {
    redRun = !redRun;
}

void switch3() {
  runSleep = !runSleep;
}

void switch4() {
  onOff = !onOff;
}

void potentiometer1(){

}

void potentiometer2(){
    
}


//    on state 
//    blinks 10 times and pauses 
void on(){
    for(int i = 0; i < 10; i++){
        digitalWrite(redLED, HIGH);
        delay(50);
        digitalWrite(redLED, LOW);
        delay(50);
    }
    delay(2000);
}

//    diagnostic state
//    blinks n times for n list of problems 
void diagnostic(int errorCode){
    for(int i = 0; i < errorCode; i++){
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);
        delay(900);
    }
}


unsigned long blueLastFade = 0;
unsigned long greenLastFade = 0;
int fadeCount = 0;
volatile float currBrightness = brightness;

// General Purpose. Fades an LED over a timer
// @params:
//  &lastFade is the last known time in ms

bool fade(unsigned long &lastFade, int pin, int time_delay){
    // Following conditional checks if the delta of the last known time (ms)
    // to the current time (ms) is valid. Hardcoded "steps" is from full
    // bright to dark is 100.
    if(millis() - lastFade >= time_delay / 100){
        currBrightness -= (float) brightness / 100;
        analogWrite(pin, currBrightness);
        lastFade = millis();
    }
    // Returns true if the fade is completed.
    if(currBrightness <= 0){
        currBrightness = brightness;
        return true;
    }
    return false;
}

unsigned long lastMillis = 0;
bool blueLEDState = 0;
int blinkOrFade = 0;


//    sleep state
//    blink 4 times in one second, then fade over one second
void sleep(unsigned long &last, bool &blueLEDState, int &blinkOrFade){
    // Count of 6 to blink 3 times (on/off 6 times total), then fades once
    // count ha
    if(blinkOrFade < 6){
        if(millis() - last >= 125){
            blueLEDState = !blueLEDState; // Toggle the LED from On to Off
            analogWrite(blueLED, blueLEDState * brightness);
            last = millis();
            blinkOrFade++;
        }
    } else {
        if(fade(blueLastFade, blueLED, 1000)){
            blinkOrFade = 0;
        }
        
    }
   
}


bool greenBlinkState = 0;
bool greenLEDState = 0;
int greenLast = 0;
int greenCount = 0;

int blueLast = 0;

void run(){

    if(greenBlinkState){
        if(millis() - greenLast >= 250){
            greenLEDState = !greenLEDState; 
            analogWrite(greenLED, greenLEDState * brightness);
            greenLast = millis();
            greenCount++;
            Serial.println("green switch");
        }

        if(greenCount > 4){
            greenCount = 0;
            greenBlinkState = false;
        }
    }

    if(!greenBlinkState){       
        if(fade(greenLastFade, greenLED, 6000)){
            greenBlinkState = true;
        } 
    }



    if(blueRun){
        if (abs(millis() - blueLast) >= 50) {
            blueLEDState = !blueLEDState;
            analogWrite(blueLED, blueLEDState * brightness);
            blueLast = millis();
        }
    } else {
        if (abs(millis() - blueLast) >= 500) {
            blueLEDState = !blueLEDState;
            analogWrite(blueLED, blueLEDState * brightness);
            blueLast = millis();
        }
    }

    if(redRun and blueRun){
        analogWrite(redLED, brightness);
    } 

    if(!blueRun){
        digitalWrite(redLED, LOW);
    }
}

void pins(){
    //pinModes
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);

    pinMode(switch1pin, INPUT_PULLUP);
    pinMode(switch2pin, INPUT_PULLUP);
    pinMode(switch3pin, INPUT_PULLUP);
    pinMode(switch4pin, INPUT_PULLUP);

    pinMode(potentiometer1pin, INPUT_PULLUP);
    pinMode(potentiometer2pin, INPUT_PULLUP);
}

void attachingInterrupts(){
    //interrupts
    attachInterrupt(digitalPinToInterrupt(switch1pin), switch1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch2pin), switch2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch3pin), switch3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch4pin), switch4, CHANGE);
}

enum states {OFF, ON, DIAGNOSTIC, SLEEP, RUN}; 

enum states state; 

void setup()
{
    Serial.begin(9600);

    Serial.println("Initializing"); 
    //initializing
    pins();
    attachingInterrupts();

    blueRun = !digitalRead(switch1pin);
    redRun = !digitalRead(switch2pin);
    onOff = !digitalRead(switch4pin);
    runSleep = !digitalRead(switch3pin);


    //enum states state = onOff ? ON : OFF; 
}

// execute state machine functionality
void loop()
{
    brightness = map(analogRead(A0), 0, 673, 0, 255);
    flashPattern = analogRead(A1);
    Serial.println(brightness);

    switch(state) {
        case OFF:
            digitalWrite(redLED, 0);
            digitalWrite(greenLED, 0);
            digitalWrite(blueLED, 0);
            if (onOff == HIGH) {
                state = ON;
            }
            break; 
        case ON: 
            digitalWrite(greenLED, 0);
            digitalWrite(blueLED, 0);
            on();
            state = DIAGNOSTIC; 
            break; 
        case DIAGNOSTIC:
            diagnostic(errorCode);
            state = SLEEP;
            break; 
        case SLEEP:
            digitalWrite(greenLED, 0);
            if(runSleep == HIGH){
                state = RUN; 
            }
            sleep(lastMillis, blueLEDState, blinkOrFade);
            break;
             
        case RUN: 
            if(runSleep == LOW){
                state = SLEEP; 
            }
            run();
            break; 
    }

    if(onOff == 0){
        state = OFF;
    } 
}

