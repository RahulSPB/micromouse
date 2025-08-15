#ifndef ENCODERS_H
#define ENCODERS_H
#include "config.h"

extern volatile long encLeft;
extern volatile long encRight;

void IRAM_ATTR isrLeft();
void IRAM_ATTR isrRight();

class Encoders {
public:
  static void init();
  static inline long left()  { return encLeft;  }
  static inline long right() { return encRight; }
  static void reset();
};

#endif
