#include <Arduino>

#include "chall1.h"
#include "utils.h"
#include "drive.h"
#include "pins.h"
#include "colors.h"
#include "light_comm.h"
#include "wifi_comm.h"

void Chall1::bot1_run() {
  Drive drive;
  Light_Comm lightComm;
  Wifi_Comm wifiComm;

  bot1_start();

  drive.forwardToWall();

  drive.rightPointTurn(160);

  drive.forwardToColor(red);
  digitalWrite(Pins::redStateLED, HIGH);

  drive.leftPointTurn(200);
  drive.stop();

  lightComm.chall1_send();
  lightComm.chall1_receive();

  drive.rightPointTurn(100);
  
  bot1_follow_red(drive);

  wifiComm.chall1_red_bot1();

  drive.backwardFor(50);
  drive.leftPointTurn(90);
  
  bot1_find_yellow(drive);
  bot1_follow_yellow(drive);

  wifiComm.chall1_yellow_bot1();

  drive.backwardFor(50);
  drive.leftPointTurn(110);

  drive.forwardToWall();

  wifiComm.chall1_end();
}

void Chall1::bot1_start() {
  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  millisDelay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  millisDelay(150);

  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  millisDelay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  millisDelay(150);

  digitalWrite(Pins::redStateLED, HIGH);
  digitalWrite(Pins::blueStateLED, HIGH);
  millisDelay(150);

  digitalWrite(Pins::redStateLED, LOW);
  digitalWrite(Pins::blueStateLED, LOW);
  millisDelay(150);
}

void Chall1::bot1_follow_red(Drive drive) {
  drive.leftFollowLine(red);

  digitalWrite(Pins::redStateLED, HIGH);
  millisDelay(150);
  digitalWrite(Pins::redStateLED, LOW);
}

void Chall1::bot1_find_yellow(Drive drive) {
  drive.leftSoftCurveTurn();
  while (getColor() != yellow)
    millisDelay(10);
  drive.stop();

  digitalWrite(Pins::horn, HIGH);
  millisDelay(150);
  digitalWrite(Pins::horn, LOW);
  millisDelay(150);
  digitalWrite(Pins::horn, HIGH);
  millisDelay(150);
  digitalWrite(Pins::horn, LOW);
  millisDelay(150);

  digitalWrite(Pins::greenStateLED, LOW);
  digitalWrite(Pins::yellowStateLED, HIGH);
}

void Chall1::bot1_follow_yellow(Drive drive) {
  drive.leftPointTurn(90);
  drive.leftFollowLine(yellow);
}

void Chall1::bot2_run() {
  Drive drive;
  Light_Comm lightComm;
  Wifi_Comm wifiComm;
  volatile char *prev_buffer = malloc(65);

  lightComm.chall1_receive();
  lightComm.chall1_send();
  bot2_setup_polling(prev_buffer);

  drive.stopFor(5000);

  drive.forwardToWall();

  drive.leftPointTurn(170);

  drive.forwardToColor(blue);
  bot2_follow_blue(drive);

  wifiComm.chall1_yellow_bot2();

  drive.backwardFor(50);
  drive.rightPointTurn(90);

  bot2_find_yellow(drive);
  bot2_follow_yellow(drive);

  drive.rightPointTurn(80);
  drive.forwardToWall();

  free(prev_buffer);
  wifiComm.chall1_end();
}

void Chall1::bot2_follow_blue(Drive drive) {
  digitalWrite(Pins::blueStateLED, HIGH);
  drive.rightPointTurn(90);
  drive.rightFollowLine(blue);
  digitalWrite(Pins::blueStateLED, LOW);
  digitalWrite(Pins::greenStateLED, HIGH);
}

void Chall1::bot2_find_yellow(Drive drive) {
  drive.rightSoftCurveTurn();
  while (getColor() != yellow)
    millisDelay(10);
  drive.stop();

  digitalWrite(Pins::yellowStateLED, HIGH);
}

void Chall1::bot2_follow_yellow(Drive drive) {
  drive.rightPointTurn(70);
  drive.rightFollowLine(yellow);
}

void Chall1::bot2_setup_polling(char *init) {
  // These define's must be placed at the beginning before #include "megaAVR_TimerInterrupt.h"
  // _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
  // Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
  #define TIMER_INTERRUPT_DEBUG         0
  #define _TIMERINTERRUPT_LOGLEVEL_     0
  
  // Select USING_16MHZ     == true for  16MHz to Timer TCBx => shorter timer, but better accuracy
  // Select USING_8MHZ      == true for   8MHz to Timer TCBx => shorter timer, but better accuracy
  // Select USING_250KHZ    == true for 250KHz to Timer TCBx => shorter timer, but better accuracy
  // Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy
  #define USING_16MHZ     true
  #define USING_8MHZ      false
  #define USING_250KHZ    false
  
  #define USE_TIMER_0     false
  #define USE_TIMER_1     true
  #define USE_TIMER_2     false
  #define USE_TIMER_3     false
  
  // To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
  // https://www.arduino.cc/reference/en/libraries/megaavr_timerinterrupt/
  #include "megaAVR_TimerInterrupt.h"
  
  #define TIMER1_INTERVAL_MS    800

  // Select Timer 1-2 for UNO, 0-5 for MEGA
  // Timer 2 is 8-bit timer, only for higher frequency
  ITimer1.init();
  
  // Get initial value in server to detect change (new message)
  WifiComm::chall1_red_bot2_setup(init);

  // Using ATmega328 used in UNO => 16MHz CPU clock ,
  // For 16-bit timer 1, 3, 4 and 5, set frequency from 0.2385 to some KHz
  // For 8-bit timer 2 (prescaler up to 1024, set frequency from 61.5Hz to some KHz
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, bot2_poll_isr, init)) {
    Serial.print(F("Starting  ITimer1 OK, millis() = "));
    Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

}

void bot2_poll_isr(char *prev) {
  static bool received = false;
  
  if (!received) {
    received = WifiComm::chall1_red_bot2_poll(prev);
  }
}
