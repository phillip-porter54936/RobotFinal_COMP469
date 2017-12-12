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

GyroSensor :: GyroSensor(void)
{
 bno = Adafruit_BNO055(55); 
 bno.setExtCrystalUse(true);
}

void GyroSensor :: getUpdate(void)
{
  sensors_event_t event;
  this->bno.getEvent(&event);
  
  this->yaw   = event.orientation.x;
  this->roll  = event.orientation.y;
  this->pitch = event.orientation.z;
  
  uint8_t sys = gyro = accel = mag = 0;
  this->bno.getCalibration(&sys, &gyro, &accel, &mag);
}
  
