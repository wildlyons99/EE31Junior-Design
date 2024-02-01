/* 
 * This program is a state machine that can run five possible states:
 *      OFF, ON, DIAGNOSTIC, SLEEP, RUN
 * Each state has its own functionality, listed in its corresponding function's
 * contract. As for how states are cycled, there is a command loop in
 * "void loop()" that utilizes an enum, checking the current state and
 * performing the corresponding function. Depending on inputs via interrupts,
 * there is a conditional tied to the current state that will allow a transition
 * to the next state.
 * 
 * Authors: Chris Bann, Tom Lyons, Kinan Rabbat, and Remy Ren
 * 
 */

#include <Arduino.h>

const int redLED = 9;
const int blueLED = 10;
const int greenLED = 6;

// unimplemented error checking, generic test code for now
int errorCode = 2;

// input pins for the DIP switches
const int switch1pin = 2;                 //pin for blueLED control for run state
const int switch2pin = 3;                 //pin for redLED control for run state
const int switch3pin = 4;                 //pin for run/sleep
const int switch4pin = 5;                 //pin for on/off switch

volatile bool blueRun = 0;                //blueLED @ 10Hz when high, else 1Hz
volatile bool redRun = 0;                 //redLED on when high, else off
volatile bool onOff = 0;                  //on when high
volatile bool runSleep = 0;               //run when high

// input pins for the potentiometers
const int potentiometer1pin = A0;
const int potentiometer2pin = A1;

int brightness = 255;            // how bright the LED is
int flashPattern;

// Function for interrupt attached to DIP switch 2, changes global var. blueRun
void switch1() {
    blueRun = !blueRun;
}

// Function for interrupt attached to DIP switch 2, changes global var. redRun
void switch2() {
    redRun = !redRun;
}

// Function for interrupt attached to DIP switch 3, changes global var. runSleep
void switch3() {
  runSleep = !runSleep;
}

// Function for interrupt attached to DIP switch 4, changes global var. onOff
void switch4() {
  onOff = !onOff;
}


//  For the ON state.
//  Blinks redLED 5 times (ON/OFF), uses delay as no other functions should be
//  running at the same time as this status indicator, only sequentially.
void on(){
    for(int i = 0; i < 10; i++){
        digitalWrite(redLED, HIGH);
        delay(50);
        digitalWrite(redLED, LOW);
        delay(50);
    }
    delay(2000);
}

//    For the DIAGNOSTIC state.
//    Blinks n times for n list of problems, indicated by...
//      arguments: errorCode
//    (true functionality not yet implemented, no real error checking yet)
void diagnostic(int errorCode){
    for(int i = 0; i < errorCode; i++){
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);
        delay(900);
    }
}

// global tracking last time the fade function was entered for the blue LED
unsigned long blueLastFade = 0;
// global tracking last time the fade function was entered for the green LED
unsigned long greenLastFade = 0;
// global used to vary the PWM of any LED in the fade function (poor practice)
volatile float currBrightness = brightness;

// General Purpose. Fades an LED over a timer
// @params:
//  &lastFade is the last known time in ms
bool fade(unsigned long &lastFade, int pin, int time_delay){
    // Following conditional checks if the delta of the last known time (ms)
    // to the current time (ms) is valid. Hardcoded "steps" is from full
    // bright to dark is 100.
    if(millis() - lastFade >= time_delay / 100){
        currBrightness -= (float) 255 / 100;
        analogWrite(pin, currBrightness);
        lastFade = millis();
    }
    // Returns true if the fade is completed.
    if(currBrightness <= 0){
        currBrightness = 255;
        return true;
    }
    return false;
}

// global used in the void loop() to keep track of the last time sleep() was ran
unsigned long lastMillis = 0;
// global to track state of blueLED, 1 = ON, 0 = OFF
bool blueLEDState = 0;
// global to track if blue LED should be blinking or fading
int blinkOrFade = 0;

/*
 * name:      sleep
 * purpose:   Performs the sleep state functionality, which does the following:
 *              - Blinks the blue LED 4 times in 1 second
 *              - Then fades the blue LED from ON to OFF over 1 second
 *
 * arguments: &last, to track the time delta between each sleep() call
 *            &blueLEDState, bool that tracks if the LED is ON/OFF
 *            &blinkOrFade, tracks if the LED should be blinking or fading
 *                                                        NEED I SAY MORE?
 *
 * returns:   none
 * effects:   By reference, &last, &blueLEDState, &blinkOrFade
 *            global, bluelastFade
 */
void sleep(unsigned long &last, bool &blueLEDState, int &blinkOrFade){
    // Count of 6 to blink 3 times (on/off 6 times total), then fades once
    // count ha
    if(blinkOrFade < 6){
        if(millis() - last >= 125){
            blueLEDState = !blueLEDState; // Toggle the LED from On to Off
            digitalWrite(blueLED, blueLEDState);
            last = millis();
            blinkOrFade++;
        }
    } else {
        if(fade(blueLastFade, blueLED, 1000)){ // ... uses global not in args
            blinkOrFade = 0;
        }
        
    }
   
}

// Global to track if RUN has finished blinking the green LED the reuqired
// amount of times. If HIGH, it is not done blinking. If LOW, it is done.
bool greenBlinkState = 0;
// Global tracking current state of the green LED
bool greenLEDState = 0;
// Global tracking number of times the green LED has changed state (on and off)
int greenCount = 0;

// Global to track last time (ms) the green LED state was changed
unsigned long greenLast = 0;
// Global to track last time (ms) the blue LED state was changed
unsigned long blueLast = 0;

/*
 * name:      run
 * purpose:   Performs the run state functionality, which does the following:
 *              - Turns on the green LED and fades it over 6 sec.
 *              - Then blinks green LED twice, duty cycle lasting 0.5 sec
 *              - Blue LED will flash at a rate of either 10hz or 1hz, changed
 *                by the variable blueRun (interrupt controlled)
 *              - Red LED is controlled by redRun (interrupt controlled)
 *
 * arguments: &greenLast, to track the time delta between each run() call
 *            &blueLast, ditto fucntionality but for blueLED
 *            &greenLEDState, bool that tracks if the LED is ON/OFF
 *
 * returns:   none
 * effects:   By reference, &greenLast, &blueLast, &greenLEDState
 */
void run(unsigned long &greenLast, unsigned long &blueLast, bool &greenLEDState){
    // Checking if the green LED is ON
    if(greenBlinkState){
        if(millis() - greenLast >= 250){ // Will change green LED every ~250 ms
            greenLEDState = !greenLEDState; 
            digitalWrite(greenLED, greenLEDState);
            greenLast = millis();
            greenCount++;

        }

        if(greenCount > 4){ // Redundant if greenBlinkState was just this (?)
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
        if (abs(millis() - blueLast) >= 50) { // Will change blue LED ~50 ms
            blueLEDState = !blueLEDState;
            analogWrite(blueLED, blueLEDState * brightness);
            blueLast = millis();
        }
    } else {
        if (abs(millis() - blueLast) >= 500) { // Will change blue LED ~500 ms
            blueLEDState = !blueLEDState;
            analogWrite(blueLED, blueLEDState * brightness);
            blueLast = millis();
        }
    }

    if(redRun and blueRun){
        digitalWrite(redLED, HIGH);
    } 

    if(!blueRun){
        digitalWrite(redLED, LOW);
    }
}

/*
 * name:      pins
 * purpose:   sets all the modes for utilized pins
 * arguments: none
 * returns:   none
 * effects:   all the involved pins by global
 */
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

/*
 * name:      attachingInterrupts
 * purpose:   sets interrupts for all 4 DIP switches, attaching functions to IRQ
 *            The interrupts are triggered on any change to the DIP switch
 * arguments: none
 * returns:   none
 * effects:   all the involved pins by global, as well as functions
 *            switch1(), switch2(), switch3(), switch4()
 */
void attachingInterrupts(){
    //interrupts
    attachInterrupt(digitalPinToInterrupt(switch1pin), switch1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch2pin), switch2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch3pin), switch3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(switch4pin), switch4, CHANGE);
}

// enum list of all desired, possible states
enum states {OFF, ON, DIAGNOSTIC, SLEEP, RUN}; 

// Global var that keeps track of the curent state among the possible states
enum states state; 

void setup()
{
    Serial.begin(9600);

    Serial.println("Initializing"); 
    // initializing functions
    pins();
    attachingInterrupts();

    // Inverting due to physical behavior of DIP switches, where the ON label
    // conflicted with the position of the switch.
    blueRun = !digitalRead(switch1pin);
    redRun = !digitalRead(switch2pin);
    onOff = !digitalRead(switch4pin);
    runSleep = !digitalRead(switch3pin);
}

// To continually execute state machine functionality!
void loop()
{
    brightness = map(analogRead(A0), 0, 673, 0, 255);
    flashPattern = map(analogRead(A1), 0, 673, 1, 10);
    Serial.println(flashPattern);

    switch(state) {
        case OFF:
            // Ensure all LEDs cannot be on (per spec)
            digitalWrite(redLED, 0);
            digitalWrite(greenLED, 0);
            digitalWrite(blueLED, 0);
            // Change state if on/off switch is toggled HIGH
            if (onOff == HIGH) {
                state = ON;
            }
            break; 
        case ON: 
            // Ensure unused LEDs in this mode are off (per spec)
            digitalWrite(greenLED, 0);
            digitalWrite(blueLED, 0);
            // Run the ON state functionality
            on();
            // Go right to the DIAGNOSTIC state after
            state = DIAGNOSTIC; 
            break; 
        case DIAGNOSTIC:
            // If there is an error code (at the moment just an integer), blink
            // the red LED the corresponding number of times
            diagnostic(errorCode);
            state = SLEEP;
            break; 
        case SLEEP:
            // Ensure unused LEDs in this mode are off (per spec)
            digitalWrite(greenLED, 0);
            // Change state to RUN if switch other than on/off was toggled
            if(runSleep == HIGH){
                state = RUN; 
            }
            sleep(lastMillis, blueLEDState, blinkOrFade); // global lastMillis
            break;
             
        case RUN:
            if(runSleep == LOW){
                state = SLEEP; 
            }
            run(greenLast, blueLast, greenLEDState);
            break; 
    }

    // In any event the on/off switch is toggled to LOW, next state is OFF
    if(onOff == 0){
        state = OFF;
    } 
}

