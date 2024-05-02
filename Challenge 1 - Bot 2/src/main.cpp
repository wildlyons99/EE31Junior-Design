// Arduino Lib
#include <Arduino.h>

// Our Helper Files
#include "motors.h"
#include "horn_and_lights.h"
#include "collision_detection.h"
#include "color_detection.h"
#include "follow_line.h"
#include "wifi_comm.h"
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
}

void loop()
{   
    send_mqtt("Trying to recieve a message..."); 

    get_message("state=go"); 
    POSTServer(postRoute, "state=go"); 

    send_mqtt("Got message to go!"); 

    chall1_send();

    delay(5000); 

    // begin challenge 1

    const char forward[] = "$$$F1"; 

    send_mqtt(forward); 
    // drive pretty much straigh to the wall until detects collision
    drive_forward();


    // keep driving until collision detected
    while (!obsticle())
        delay(100);

    // then stop
    stop_all();
    
    const char forward_stop[] = "$$$F0"; 
    send_mqtt(forward_stop); 

    Serial.println("Obsticle");

    delay(1000);

    // turn around and go back until find the red line
    turn_left(turn_right_180);
    
    send_mqtt(forward); 

    drive_forward();
    send_mqtt(forward_stop);

    while (detectColor() != Blue)
        ;
    stop_all();

    // Once bot comes back and finds the red line, blink red light
    digitalWrite(blueStatus, HIGH);

    const char blue[] = "$$$blue"; 
    send_mqtt(blue); 

    follow_line(Blue);

    const char none[] = "$$$none"; 
    send_mqtt(none);

    // After stopping at wall, THEN
    digitalWrite(blueStatus, LOW); // set LED low to allow for blinking
    delay(50); 

    digitalWrite(greenStatus, HIGH);

    BlinkRedStatus(); 

    send_mqtt("Waiting for red message!"); 

    get_message("state=red"); 
    POSTServer(postRoute, "state=red");

    send_mqtt("Sent red message!"); 

    // a config feature for if we need to reconfigure sensor values
    detectColor();
    delay(750);

    send_mqtt("Waiting for yellow message!"); 

    get_message("state=yellow"); 
    
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

    turn_right(turn_right_180 / 2);

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

    const char yellow[] = "$$$yellow"; 
    send_mqtt(yellow); 

    // follow the yellow line
    follow_line(Yellow);

    send_mqtt(none); 

    // Tell bot 2 to continue

    // go backwards
    go_backwards(1000); 

    // turn_left()
    turn_right(turn_right_180 / 2);

    // drive back to wall
    drive_forward();
    while (!obsticle())
        delay(100);

    stop_all();

    turn_left(turn_right_180);

    POSTServer(postRoute, "state=done"); 
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
    
    while (int val = isSubstring(message, state) == -1 && val < 6) {
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