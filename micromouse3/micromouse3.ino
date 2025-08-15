#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

#include "config.h"
#include "Motors.h"
#include "Encoders.h"
#include "Sensors.h"
#include "Control.h"
#include "MazeSolver.h"

// Global IMU
MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  delay(200);

  // I2C + IMU
  Wire.begin(I2C_SDA, I2C_SCL);
  byte s = mpu.begin();
  Serial.print("MPU6050 status: "); Serial.println(s);
  if (s != 0) { Serial.println("IMU init failed"); while(1) delay(10); }
  Serial.println("Calibrating IMU... keep still");
  delay(1000);
  mpu.calcOffsets();

  // Subsystems
  Motors::init();
  Encoders::init();
  Sensors::init();
  Control::init();

  Serial.println("Setup done.");
  delay(500);
}

void loop() {
  // Example: run left-wall follower for a handful of steps
 /*
  for (int i = 0; i < 4; ++i) {
    MazeSolver::runLeftWallOnce();
    delay(200);
  }
  */
  // Stop here (replace with your flood-fill later)
  
  while (true) { delay(1000); }
}
