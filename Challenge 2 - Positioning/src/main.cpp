#include <Arduino.h>

#include <string.h>
#include <stdbool.h>

#include "motors.h"
#include "pins.h"
#include "light_comm.h"
#include "wifi_comm.h"

void setup() {
  // put your setup code here, to run once:
  setup_motors();
  Pins pinobject;
  pinobject.setPins();
  Serial.begin(9600);
  delay(3000);
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

/* Challenge 2 Requirements
  Communicate with other bot (NOT DONE HERE AS OF 4/28/24)
  Move forwards 12in
  Stop
  turn 180 deg
  Stop
  move backwards 3in
  Stop
  turn left
  turn right
  turn right
*/
// Light_Comm lightcomm;
char messageData[515];

int bot_num = 2; 

void loop() {
    /* 
    wifi_connect(); 

    // format of postRoute: "POST /senderID/receiverID HTTP/1.1"
    char postRoute[] = "POST /A20F65BA5E3C/89C87865077A HTTP/1.1"; // sending from ourselves to ourselves

    // format of gettRoute: "GET /senderID/receiverID HTTP/1.1"
    char getRoute[] = "GET /A20F65BA5E3C/89C87865077A HTTP/1.1";

    char message[65]; // Maximum length of message is 64 characters

    // lightcomm.chall1_receive();
    if (bot_num == 1) {
        POSTServer(postRoute, "go=false");
        // dest, source, size
        memcpy(message, "go=true", 9); 
    } else if (bot_num == 2) {
        POSTServer(postRoute, "go=true"); 
        // dest, source, size
        memcpy(message, "go=false", 9); 
    }

    delay(5000); 

    
    while (isSubstring(message, "go=true") == -1) {
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
    */
    
    unsigned int now = millis(); 

    while (millis() - now <= 9800) { // Move forwards 12 inches
        go_forward(110); 

        delay(100); 
    }

    delay(1000); // Stop

    turn_right(1100); // Turn 180 deg right

    delay(1000); // Stop

    now = millis();
    while (millis() - now <= 3900) { // Move backwards 3 inches
        go_backwards(110); 

        delay(100); 
    }

    delay(1000); // Stop

    turn_left(590); // Turn 90 deg left

    for (int i = 0; i < 2; i++) {
      delay(250); // rest

      turn_right(580); // Turn 90 deg right
    }

    delay(250); // rest
    turn_right(575); // Turn 90 deg right

    now = millis();
    while (millis() - now <= 14100) { // Move backwards ~15 inches
        go_backwards(110); 

        delay(100); 
    }

    /*

    if (bot_num == 1) {
        Serial.println("Sending go!"); 
        POSTServer(postRoute, "go=true");
    } else if (bot_num == 2) {
        POSTServer(postRoute, "go=false"); 
    } else {
        Serial.print("uh oh"); 
        exit(1); 
    }

    delay(2000); 

    POSTServer(postRoute, "go=false"); 
    Serial.println("Done with execution"); 

    */

    while(1); 
}