// Code tuned for robot 3
// modified: 10/03/2017, Houman Dallali
// modified: 10/19/17   Phillip Porter
// COMP 590

#include <Servo.h>


void move_forward()
{
  moving = true;
  int power0, power1;
  int error0, error1;

    // proportional feedback gain:
    int kp=8;
        
    float turns0    = ((float)encoder0Pos)/ROTATION_1;
    float turns1    = ((float)encoder1Pos)/ROTATION_2;
    
    // desired no. of turns for motor0
    float desTurns0 = 5;
    error0=kp*(desTurns0-turns0); 
    // desired no. of turns for motor1
    
    float desTurns1 = 5;
    error1=kp*(desTurns1-turns1); 

    // Control of Motor 0
    if (error0 < -.05)
    {
      power0=60;
      //power0=map(error0,-10*kp, 10*kp, 10,80);
    }
    else if (error0 < .05)
    {
      power0 = 90;
    }
    else
    {
      power0=120;
      //power0=map(error0,-10*kp, 10*kp, 175,90);
    }
       
    // Control Calc for Motor 1
    if (error1 < -.05)
    {
      power1 = 60;
      //power1=map(error1,-10*kp, 10*kp, 100,120);
    }
    else if (error1 < .05)
    {
      power1 = 95;
    }
    else
    {
      power1=120;
      //power1=map(error1,-10*kp, 10*kp, 80,50);
    }
    ST0.write(power0);
    ST1.write(power1);
    
    delay(Ts/8);

  encoder0PinALast = n;
  valNew = encoder0Pos;
  if (valNew != valOld) {
    valOld = valNew;
  }

  encoder1PinALast = n1;
  valNew1 = encoder1Pos;
  if (valNew1 != valOld1) {
    valOld1 = valNew1;
  }
  
  // printing encoder values to serial monitor
  Serial.print(" Enc0 Pos: ");
  Serial.print (encoder0Pos, DEC);
  Serial.print(" Enc1 Pos: ");
  Serial.print (encoder1Pos, DEC); 
  Serial.print(" Error1: ");
  Serial.print(error1, DEC);
  Serial.print(" Power1: ");
  Serial.println(power1, DEC);
  
  if (power0 == 90 && power1 == 95)
  {
     moving=false; 
  }
   
  loopCnt++;
}

void CountA()
{
  n = digitalRead(encoder0PinA); 
  if ((encoder0PinALast == LOW) && (n == HIGH)) { 
    if (m == LOW) { 
      encoder0Pos--; 
    } 
    else { 
      encoder0Pos++; 
    } 
  }
}

void StateB()
{
  m = digitalRead(encoder0PinB);
}


void CountA1()
{
  n1 = digitalRead(encoder1PinA); 
  if ((encoder1PinALast == LOW) && (n1 == HIGH)) { 
    if (m1 == LOW) { 
      encoder1Pos++; 
    } 
    else { 
      encoder1Pos--; 
    } 
  }
}

void StateB1()
{
  m1 = digitalRead(encoder1PinB);
}

