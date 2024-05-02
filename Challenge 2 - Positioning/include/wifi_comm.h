#ifndef __WIFI_COMM__
#define __WIFI_COMM__

#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

// char server[] = "ee31.ece.tufts.edu";    // name address for (using DNS)

// int keyIndex = 0;             // network key Index number (needed only for WEP)
// int portNumber = 80;          // defult 
// int status = WL_IDLE_STATUS;

void printWifiStatus(); 

void wifi_connect(); 

void GETServer(const char theRoute[], char *message); 
void POSTServer(const char theRoute[], char *bodyMessage); 


#endif