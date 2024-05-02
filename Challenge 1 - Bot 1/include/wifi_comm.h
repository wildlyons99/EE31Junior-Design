#ifndef __WIFI_COMM__
#define __WIFI_COMM__

#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

void send_mqtt(const char msg[]); 
void send_mqtt_string(String msg); 

void printWifiStatus(); 

void wifi_connect(); 

void GETServer(const char theRoute[], char *message); 
void POSTServer(const char theRoute[], char *bodyMessage); 


#endif