/*
 * drive.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 * 2/24/2024
 *
 */

#ifndef __DRIVE_H__
#define __DRIVE_H__

#include <Arduino.h>
#include "colors.h"

struct Drive {
public:
  void forward();
  void backward();
  void leftCurveTurn();
  void leftSoftCurveTurn();
  void rightCurveTurn();
  void rightSoftCurveTurn();
  void stop();

  void leftFollowLine(color c);
  void rightFollowLine(color c);
  void forwardToWall();
  void forwardToColor(color c);

  void forwardFor(int time);
  void backwardFor(int time);
  void leftPointTurn(unsigned long degrees);
  void rightPointTurn(unsigned long degrees);
  void stopFor(int time);
};

#endif
