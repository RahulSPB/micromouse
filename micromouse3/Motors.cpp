#include "Motors.h"
#include <Arduino.h>

static inline void setHBridge(int in1, int in2, int speedAbs, int pwmChannel) {
  if (speedAbs == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(pwmChannel, 0);
    return;
  }
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  ledcWrite(pwmChannel, speedAbs);
}

void Motors::init() {
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_BIN1, OUTPUT);
  pinMode(PIN_BIN2, OUTPUT);
  pinMode(PIN_STBY, OUTPUT);
  digitalWrite(PIN_STBY, HIGH); // enable TB6612

  // LEDC PWM setup

  //ledcSetup(PWM_CH_LEFT,  PWM_FREQ_HZ, PWM_RES_BITS);
  //ledcAttachPin(PIN_PWMA, PWM_CH_LEFT);
  ledcAttach(PIN_PWMA, PWM_FREQ_HZ, PWM_RES_BITS);


  //ledcSetup(PWM_CH_RIGHT, PWM_FREQ_HZ, PWM_RES_BITS);
  //ledcAttachPin(PIN_PWMB, PWM_CH_RIGHT);
  ledcAttach(PIN_PWMB, PWM_FREQ_HZ, PWM_RES_BITS);

  brake();
}

void Motors::setLeft(int pwm) {
  pwm = constrain(pwm, -PWM_MAX, PWM_MAX);
  if (pwm >= 0) { // forward
    digitalWrite(PIN_AIN1, HIGH);
    digitalWrite(PIN_AIN2, LOW);
    ledcWrite(PWM_CH_LEFT, pwm);
  } else { // reverse
    digitalWrite(PIN_AIN1, LOW);
    digitalWrite(PIN_AIN2, HIGH);
    ledcWrite(PWM_CH_LEFT, -pwm);
  }
}

void Motors::setRight(int pwm) {
  pwm = constrain(pwm, -PWM_MAX, PWM_MAX);
  if (pwm >= 0) {
    digitalWrite(PIN_BIN1, HIGH);
    digitalWrite(PIN_BIN2, LOW);
    ledcWrite(PWM_CH_RIGHT, pwm);
  } else {
    digitalWrite(PIN_BIN1, LOW);
    digitalWrite(PIN_BIN2, HIGH);
    ledcWrite(PWM_CH_RIGHT, -pwm);
  }
}

void Motors::brake() {
  // short brake
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, HIGH);
  digitalWrite(PIN_BIN1, HIGH);
  digitalWrite(PIN_BIN2, HIGH);
  ledcWrite(PWM_CH_LEFT, 0);
  ledcWrite(PWM_CH_RIGHT, 0);
}
