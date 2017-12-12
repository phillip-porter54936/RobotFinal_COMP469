// Move_Control
// This code controls movement via Gyro sensor and Lidar
// and does so by control from serial
// COMP 469

#include <Servo.h>
// Serial constants
#define STOP_BYTE ';'
#define COUNT_COMMANDS 2

// Motor constants
#define ROTATION_1 340
#define ROTATION_2 350

// Motor variables

// encoder0
int encoder0PinA = 2;
int encoder0PinB = 3;
volatile int encoder0Pos = 0;
volatile int encoder0PinALast = LOW;
volatile int n = LOW;
int valNew = 0;
int valOld = 0;
volatile int m = LOW;

// encoder1
int encoder1PinA = 18;
int encoder1PinB = 19;
volatile int encoder1Pos = 0;
volatile int encoder1PinALast = LOW;
volatile int n1 = LOW;
int valNew1 = 0;
int valOld1 = 0;
volatile int m1 = LOW;

int loopCnt=0;
int Ts = 1; //1ms

Servo ST0, ST1;
boolean moving = false;

// Controller variables
String buffer = "";
String commands[] = {"MOVE", "TURN"};
enum {MOVE, TURN};

void setup()
{
  // Motor setup
  ST0.attach(9, 1000, 2000);
  ST1.attach(10, 1000, 2000);

  // encoder0 setup
  pinMode (encoder0PinA,INPUT); 
  pinMode (encoder0PinB,INPUT);
  attachInterrupt(encoder0PinB, CountA, CHANGE);
  attachInterrupt(encoder0PinA, StateB, FALLING);
  
   // encoder1 setup
  pinMode (encoder1PinA,INPUT); 
  pinMode (encoder1PinB,INPUT);
  attachInterrupt(encoder1PinB, CountA1, CHANGE);
  attachInterrupt(encoder1PinA, StateB1, FALLING); 
  
  Serial.begin(9600);
}

void loop()
{
  // Accumulate bytes from serial
  int i = 0; char char_in;
  do
  {
    char_in = Serial.read();
    Serial.print(char_in);
    buffer+=char_in;
  }
  while (char_in != STOP_BYTE);
  
  String cmd_code = buffer.substring(0,4);
  
  int cmd_index;
  for (cmd_index=0; cmd_index<COUNT_COMMANDS;cmd_index++)
    if (cmd_code == commands[cmd_index]) break;
    
  switch(cmd_index)
  {
     case MOVE: 
     // Move forward one space
       do 
       {
         move_forward();
       } while (moving);
     break;
     case TURN: 
     
     break;
  }
}
