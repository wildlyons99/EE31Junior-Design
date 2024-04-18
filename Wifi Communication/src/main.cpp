/* main.cpp
 * Phase 4 Wifi Comms
 * ee31 Junior Deisgn
 */

// Arduino Libs
#include <Arduino.h>

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;    // network SSID (name)
char pass[] = SECRET_PASS;    // network password 

int keyIndex = 0;             // network key Index number (needed only for WEP)
int portNumber = 80;          // defult 
int status = WL_IDLE_STATUS;

// const int buffer_size = 1024; 
// char buffer[buffer_size]; 

// IP Addy:
// IPAddress server(xxx,xxx,xxx,xxx);  // numeric IP for (no DNS)
// DNS:
char server[] = "ee31.ece.tufts.edu";    // name address for (using DNS)

// post parameters to be sent (just for testing here, will be replaced by the actual data)
char postBody[] = "hello this is a test";

#define TEAM_RED_UUID A20F65BA5E3C
#define PURPLE_MOUNTAIN 89C87865077A

// format of postRoute: "POST /senderID/receiverID HTTP/1.1"
// char postRoute[] = "POST /TEAM_RED_UUID/PURPLE_MOUNTAIN HTTP/1.1"; // for when both online
//char postRoute[] = "POST /89C87865077A/89C87865077A HTTP/1.1"; // sending from ourselves to ourselves
//char postRoute[] = "POST /8050D1451904/8050D1451904 HTTP/1.1"; // sending from ourselves to ourselves
char postRoute[] = "POST /A20F65BA5E3C/A20F65BA5E3C HTTP/1.1"; // sending from ourselves to ourselves


// format of gettRoute: "GET /senderID/receiverID HTTP/1.1"
// char getRoute[] = "GET /89C87865077A/8050D1451904 HTTP/1.1";
//char getRoute[] = "GET /8050D1451904/8050D1451904 HTTP/1.1"; 
char getRoute[] = "GET /A20F65BA5E3C/A20F65BA5E3C HTTP/1.1"; 

// defining client
WiFiClient client;

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

// post message from sender to the receiver
void POSTServer(const char theRoute[], char *bodyMessage) {
  if (client.connect(server, portNumber)) {
    client.println(theRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    int postBodyLength = strlen(bodyMessage);
    client.println(postBodyLength);
    client.println(); // end HTTP header
    client.print(bodyMessage);

    delay(200);

    // print out the client response
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
}

// get message 
void GETServer(const char theRoute[], char *message) {
  if (client.connect(server, portNumber)) {
    Serial.println("In get server"); 
    // Make a HTTP GET request:
    client.println(theRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    delay(200);

    // index for writing to message buffer
    int messageIndex = 0;

    // print out the client response
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        message[messageIndex++] = c;
        // Check if the buffer is full
        int buffer_size = 21; 
        if (messageIndex >= buffer_size) {
          break; // Stop reading to avoid overflow
        }
      }
    }

    // add null terminator at the end of the message
    message[messageIndex] = '\0';

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
}

// this is the variable we are going to pass the info to, length tbd
char messageData[15];

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect


  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    
    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");

  // Try one POST
  POSTServer(postRoute, postBody);
  delay(200);

  // Try one GET
  GETServer(getRoute, messageData);
}

void loop() {
  // Actual implementation tbd 
}