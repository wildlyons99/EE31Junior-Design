#ifndef __COLOR_DETECTION__
#define __COLOR_DETECTION__

#include "pins.h"

enum colors {None, Black, Blue, Yellow, Red};

void setup_color_detection(); 
enum colors detectColor(); 

#endif