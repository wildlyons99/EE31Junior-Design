/*
 * colors.h
 * Purple Mountain Majesties
 *  - Alexander Lea, Connor Nightingale, Eddy Zhang, Jacob Carulli
 *  4/8/2024
 *
 */

#ifndef __COLORS_H__
#define __COLORS_H__

#include <Arduino.h>
#include <string>

enum color {red, blue, yellow, black};

color getColor();
std::string colorToString(color toPrint);

#endif
