#include <RobojaxBTS7960.h>
#include <MPU6050.h>
#include <Wire.h>
#include "defs.h"
#include "utilis.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  Serial2.begin(115200) ;
  motor.begin();
 Serial.print("establised");
  // Initialize MPU6050
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  mpu.calibrateGyro();

  mpu.setThreshold(3);
}


void loop() {
  // trying PID angle control
  PID_angle() ;
  timer = millis();
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();
  // Calculate Pitch, Roll and Yaw
  yaw       = yaw + norm.XAxis * timeStep;
  // Get the angular speed
  angularSpeed  = norm.XAxis;

  delay((timeStep * 1000) - (millis() - timer));

// Bluetooth communication protocol.
  if (Serial2.available()) {
    if (Serial2.read() == 1 && !startCommFlag)
    {
      // Connection established
      startCommFlag = 1;
      dirFlag = Serial2.read();
      reqSpdValue = Serial2.read();
      reqAngValue = Serial2.read();
    }
    
    
  }
  ypr.data.y = yaw;
  ypr.data.spd = angularSpeed;
  ypr.data.timeValue = micros() / (float)1000000;


  if (startCommFlag)
  {
    delay(50);
    Serial2.write(ypr.dataStream, dataSize) ;
    Serial2.flush();
    startCommFlag = 0;
  }
}
