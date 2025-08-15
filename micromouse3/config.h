#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ---------- GEOMETRY / ODOMETRY ----------
#define WHEEL_DIAMETER_MM   32.0f
#define WHEEL_BASE_MM       75.0f
#define CELL_SIZE_MM        180.0f   // 18 cm

// N25 encoder assumptions (adjust if different)
#define ENCODER_PPR_MOTOR   11       // pulses per motor shaft rev (single channel)
#define GEAR_RATIO          30.0f    // gearbox
// effective pulses at wheel shaft if decoding only A (CHANGE):
#define PULSES_PER_WHEEL_REV (ENCODER_PPR_MOTOR * GEAR_RATIO)   // 330
#define PI_F 3.14159265f
#define WHEEL_CIRC_MM       (PI_F * WHEEL_DIAMETER_MM)
#define PULSES_PER_MM       (PULSES_PER_WHEEL_REV / WHEEL_CIRC_MM)
#define PULSES_PER_CELL     (PULSES_PER_MM * CELL_SIZE_MM)

// ---------- PINS (ESP32 NodeMCU-32S) ----------
/* TB6612FNG */
#define PIN_AIN1  19
#define PIN_AIN2  23
#define PIN_PWMA  18
#define PIN_BIN1  17
#define PIN_BIN2  16
#define PIN_PWMB  4
#define PIN_STBY  5

/* Encoders (use interrupt-capable GPIOs) */
#define PIN_ENC_L_A  32
#define PIN_ENC_L_B  33
#define PIN_ENC_R_A  25
#define PIN_ENC_R_B  26

/* IR sensors */
#define PIN_IR_FRONT   34   // analog
#define PIN_IR_LEFT    27   // HS-S02A digital
#define PIN_IR_RIGHT   14   // HS-S02A digital
#define WALL_DETECTED  HIGH

/* I2C */
#define I2C_SDA 21
#define I2C_SCL 22

// ---------- LEDC PWM ----------
#define PWM_FREQ_HZ      20000       // 20 kHz = quiet
#define PWM_RES_BITS     10          // 0..1023
#define PWM_CH_LEFT      0
#define PWM_CH_RIGHT     1
#define PWM_MAX          ((1<<PWM_RES_BITS)-1)

// ---------- CONTROL / PID ----------
#define BASE_SPEED_PWM         520   // ~50% duty (0..1023)
#define FWD_SPEED_PWM          620
#define TURN_SPEED_PWM         500
#define MAX_CORR_PWM           220

// PID (start points; tune on robot)
#define KP_DIST  0.8f
#define KI_DIST  0.02f
#define KD_DIST  0.08f

#define KP_HEAD  2.2f
#define KI_HEAD  0.00f
#define KD_HEAD  0.45f

#define KP_TURN  3.0f
#define KI_TURN  0.00f
#define KD_TURN  1.2f

// Sensors
#define FRONT_STOP_DIST_CM   10.0f   // stop if wall < 10 cm
#define GYRO_DEADZONE_DPS    0.5f    // ignore small drift

#endif
