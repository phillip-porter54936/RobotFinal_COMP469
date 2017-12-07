// Move_Control
// This code controls movement via Gyro sensor and Lidar
// and does so by control from serial
// COMP 469

#include <Servo.h>
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  static int count = 0;
  if (Serial.available())
  {
    Serial.print((char)(Serial.read()));
    if (count++ > 60)
    {
      Serial.println("");
      count = 0;
    }
  }
}
