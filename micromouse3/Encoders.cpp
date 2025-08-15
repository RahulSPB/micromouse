#include "Encoders.h"
#include <Arduino.h>

volatile long encLeft  = 0;
volatile long encRight = 0;

void IRAM_ATTR isrLeft() {
  // Direction by comparing channels
  bool a = digitalRead(PIN_ENC_L_A);
  bool b = digitalRead(PIN_ENC_L_B);
  encLeft += (a == b) ? +1 : -1;
}

void IRAM_ATTR isrRight() {
  bool a = digitalRead(PIN_ENC_R_A);
  bool b = digitalRead(PIN_ENC_R_B);
  encRight += (a == b) ? +1 : -1;
}

void Encoders::init() {
  pinMode(PIN_ENC_L_A, INPUT_PULLUP);
  pinMode(PIN_ENC_L_B, INPUT_PULLUP);
  pinMode(PIN_ENC_R_A, INPUT_PULLUP);
  pinMode(PIN_ENC_R_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_L_A), isrLeft,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_R_A), isrRight, CHANGE);
  reset();
}

void Encoders::reset() {
  encLeft = 0;
  encRight = 0;
}
