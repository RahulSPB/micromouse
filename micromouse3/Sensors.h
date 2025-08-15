#ifndef SENSORS_H
#define SENSORS_H
#include "config.h"

class Sensors {
public:
  static void init();
  static float frontDistanceCm(); // GP2Y0A21YK0F
  static bool wallLeft();
  static bool wallRight();
};

#endif
