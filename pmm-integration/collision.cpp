#include <Arduino>

#include "collision.h"
#include "pins.h"

bool collision_detected() {
  return analogRead(Pins::collisionLED) > collision_threshold;
}
