#ifndef Gyro_h 
#define Gyro_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
using namespace std;

#define BNO055_SAMPLERATE_DELAY_MS (100)

class GyroSensor
{
private: 
  float yaw, roll, pitch;
  uint8_t sys, gyro, accel, mag;
    Adafruit_BNO055 bno;

public:
  GyroSensor(void);
  void getUpdate(void);
  float getYaw(void);    // Z
  float getRoll(void);   // X
  float getPitch(void);  // Y
  uint8_t getCalSys(void);
  uint8_t getCalGyro(void);
  uint8_t getCalAccel(void);
  uint8_t getCalMag(void);
};

#endif

