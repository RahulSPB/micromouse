#ifndef MOTORS_H
#define MOTORS_H
#include "config.h"

class Motors {
public:
  static void init();
  static void setLeft(int pwm);   // -PWM_MAX..+PWM_MAX
  static void setRight(int pwm);  // -PWM_MAX..+PWM_MAX
  static void brake();
};

#endif
