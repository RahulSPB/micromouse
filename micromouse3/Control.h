#ifndef CONTROL_H
#define CONTROL_H
#include "config.h"
#include "PID.h"
#include <MPU6050_light.h>

extern MPU6050 mpu;

class Control {
public:
  static void init();
  static void moveOneCell();  // forward 18 cm with heading hold
  static void turnLeft90();
  static void turnRight90();

private:
  static float readHeading(); // degrees (Z)
};

#endif
