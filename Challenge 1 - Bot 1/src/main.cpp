// Arduino Lib
#include <Arduino.h>

#include <string.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"
#include "wifi_comm.h"
#include "batteryadc.h"
#include "light_comm.h"

const int turn_right_180 = 1050;

char postRoute[] = "POST /A20F65BA5E3C/89C87865077A HTTP/1.1";

void get_message(char state[]); 

void setup()
{
    setup_motors();
    setup_color_detection();
    setup_horn();
    setup_lights();

    Serial.begin(9600);

    wifi_connect(); 

    Serial.println("Connected!"); 

    int motorPercent = getPercent(6.0, 9.0, batteryOut);       
    send_mqtt_string(String("$$$levelbatt:" + String(motorPercent))); 

    Serial.print("Motor: ");
    Serial.print(motorPercent);
    Serial.print("%\n");
    POSTServer(postRoute, "state=wait"); 

    // flash blue and red LEDs three times - successfully diagnostics
    for (int i = 0; i < 3; i++) {
        digitalWrite(blueStatus, HIGH); 
        digitalWrite(redStatus, HIGH); 
        delay(200); 
        digitalWrite(blueStatus, LOW); 
        digitalWrite(redStatus, LOW); 
        delay(200); 
    }

    delay(1000);
    Serial.print("Beginning..."); 
}

void loop()
{
    // a config feature for if we need to reconfigure sensor values
    detectColor();
    delay(750);

    send_mqtt("$$$F1");

    // begin challenge 1
    // drive pretty much straigh to the wall until detects collision
    drive_forward();

    // keep driving until collision detected
    while (!obsticle())
        delay(100);

    // then stop
    stop_all();

    send_mqtt("$$$F0");

    Serial.println("Obsticle");
    send_mqtt("$$$none");

    delay(1000);

    // turn around and go back until find the red line
    turn_left(turn_right_180);

    send_mqtt("$$$obs0");

    send_mqtt("$$$F1");
    drive_forward();

    while (detectColor() != Red)
        ;
    stop_all();

    send_mqtt("$$$F0");

    // Once bot comes back and finds the red line, blink red light
    digitalWrite(redStatus, HIGH);

    turn_right(turn_right_180); 

    delay(200); 

    // TRANSMIT LIGHT MESSAGE??? // or pretend while sending wifi 
    POSTServer(postRoute, "state=go"); 
    get_message("state=go"); 
    
    turn_left(turn_right_180); 

    delay(200); 

    // After recieve message twice
    // Bot 1 flashes its headlights and brake lights twice and beeps its horn twice
    // for (int i = 0; i < 2; i++) {
    //     digitalWrite(headlights, HIGH); 
    //     digitalWrite(brake, HIGH); 
    //     honk(); 
    //     delay(200); 
    //     digitalWrite(headlights, LOW); 
    //     digitalWrite(brake, LOW); 
    //     delay(200); 
    // }


    send_mqtt("$$$red");
    follow_line(Red);

    // After stopping at wall, THEN
    digitalWrite(redStatus, LOW); // set LED low to allow for blinking
    delay(50); 
    BlinkRedStatus();

    // blinks its red LED and signals Bot 2. Bot 2 upon  receipt blinks its red LED.
    // Bot 2 signals back to Bot 1, Bot 1 blinks its red LED three  times, turns off the red LED and illuminates a green LED. 
    POSTServer(postRoute, "state=red"); 
    get_message("state=red"); 
    
    // blinks its red LED and signals Bot 2. 
    // Bot 2 signals back to Bot 1, Bot 1 blinks its red LED three  times, turns off the red LED and illuminates a green LED. 
    BlinkRedStatus(); // After recieving message back
    BlinkRedStatus();
    BlinkRedStatus();
    digitalWrite(greenStatus, HIGH);

    // Communicate with BOT 2, THEN
    // Once our bot receives message back, THEN
    headAndRear();
    honk_times(2);

    // go backwards
    go_backwards(500); 

    turn_left(turn_right_180 / 2);

    // drive forward until get to yellow line
    drive_forward();
    while (detectColor() != Yellow)
        ;
    stop_all();

    // After finding yellow, THEN
    honk_times(2);
    digitalWrite(greenStatus, LOW);
    delay(100);
    digitalWrite(yellowStatus, HIGH);

    send_mqtt("$$$yellow");

    follow_line(Yellow);

    // go backwards
    go_backwards(1000); 

    // Tell bot 2 to continue
    POSTServer(postRoute, "state=yellow"); 

    // turn_left()
    turn_left(turn_right_180 / 2);

    //send_mqtt("$$$none");

    // drive back to wall
    // send_mqtt("$$$F1");
    drive_forward();
    while (!obsticle())
        delay(100);

    stop_all();

    // send_mqtt("$$$F0");

    turn_left(turn_right_180);

    send_mqtt("$$$obs0");

    // wait for bot 2 to finish
    get_message("state=done"); 

    while (1);
}

/* isSubstring
 * Purpose: 
 *      Checks if subsring 
 */
int isSubstring(char* s1, char* s2)
{
    int M = strlen(s1);
    int N = strlen(s2);
 
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;
 
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == M)
            return i;
    }
 
    return -1;
}
char messageData[515];

void get_message(char state[]) {
    // format of gettRoute: "GET /senderID/receiverID HTTP/1.1"
    char getRoute[] = "GET /A20F65BA5E3C/89C87865077A HTTP/1.1";

    char message[65]; // Maximum length of message is 64 characters

    memcpy(message, "state=wait", 11); 
    
    while (isSubstring(message, state) == -1) {
        GETServer(getRoute, messageData);
        char *ptr = strstr(messageData, "Success&");
        
        if (ptr != NULL) {
            ptr += strlen("Success&"); // Move pointer to the start of the message
            
            // Read the message using strncpy to avoid buffer overflow
            int length = strcspn(ptr, "\0"); // Find the length of the message until the next space or end of string
            if (length > 64) // Cap the length at 64 characters
                length = 64;
            
            strncpy(message, ptr, length);
            message[length] = '\0'; // Null-terminate the string
            
            Serial.print("Message: "); Serial.println(message);
        } else {
            Serial.print("No message found.\n");
        }

        delay(500); 
    }
}