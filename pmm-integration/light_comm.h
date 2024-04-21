/*
 * light_comm.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 4/4/2024
 *
 */

#ifndef __LIGHT_COMM_H__
#define __LIGHT_COMM_H__

#include <Arduino.h>

class Light_Comm {
public:
  Light_Comm();
  void chall1_send();
  void chall1_receive();

private:
  const static int threshold;
  void chall1_msg_received();
};

#endif
