#ifndef __CHALL1_H__
#define __CHALL1_H__

#include <Arduino>
#include "drive.h"

class Chall1 {
public:
  void bot1_run();
  void bot2_run();
private:
  void bot1_start();
  void bot1_follow_red(Drive drive);
  void bot1_find_yellow(Drive drive);
  void bot1_follow_yellow(Drive drive);
};

#endif
