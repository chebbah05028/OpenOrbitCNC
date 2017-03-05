// setup right now for a UNO or NANO


#include <math.h>
#define STEPSRADIAN  123.4 // Steps per radian YOU NEED TO CHANGE THIS!
#define RX 0 // Point of Rotation X
#define RY 0 // Point of Rotation Y
// Home angle is considered 0

// Point of rotation needs to be in the middle of the the XY ala 1000mm so a 600mm linear could get to 200x 1000y to 1000x200y 
// to 1800x1000y to 1000x1800y with a 240mm circle in the middle you can't get too... 
// That needs to be added to the math.
// for a 5:1 reduction rotary at 16 microsteps with a 200 step 1.8 degree stepper it's
// 2546.479088888863 steps per radian approximately 44.444444444 steps per degree, for 2pi for 360 degree's
// pi = 3.14159265359

// Linear is considered the same steps per mm as cartesian gcode;
// Linear is considered to home at Y120X0 Might have to  Preload D and oD
// D (Distance) and oD (OldDistance)
// so plasma touch at 12CM from X0Y0 is 200 stepper per rev * 16 microsteps / 4 (1204 ball screw 4mm per rev) * 120mm
// D = oD = 50*16*120 = 800*120 = 96000

// Setup to only go Positive on steps so where do jigger is homed at Rotation 0, linear rail at 120mm
unsigned long X = 0, oX = 0, Y = 0, oY = 0, A = 0. oA = 0, D = 96000, oD = 96000;


int Xd = 4; // X Direction
int Yd = 5;
int Ap = 6; // Rotation Step
int Dp = 7; // Linear Step
int Ad = 8; // Rotation Direction
int Dd = 9; // Linear Direction
long RXd;
unsigned long RYd;
unsigned long RYd;

void setup() {
  // put your setup code here, to run once:
attachInterrupt(0,Xc,RISING);  // X step Pin 2
attachInterrupt(1,Yc,RISING); //Y step Pin 3
pinMode(Xd,INPUT);
pinMode(Yd,INPUT);
pinMode(Ap,OUTPUT);
pinMode(Dp,OUTPUT);
pinMode(Ad,OUTPUT);
pinMode(Dd,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
oA = A;
oD = D;
RXd=X-RX;
RYd=Y-RY;

  A= atan2(X-RX,Y-RY) * STEPSRADIAN; // might be better Y,X
  D= sqrt(RXd*RXd+RYd*RYd);
  if(oA!=A) {
    for (int Steps = 1;Steps<=abs(oA-A);Steps++) {
      if((oA-A) < 0 ) {
        digitalWrite(Ad,HIGH);
      } else {
        digitalWrite)Ad,LOW);
      }
      digitalWrite(Ap,HIGH);
      digitalWrite(Ap,LOW);
    }
  }
  if(oD!=D) {
    for (int Steps = 1;Steps<=abs(oD-D);Steps++) {
      if((oD-D) < 0 ) {
        digitalWrite(Dd,HIGH);
      } else {
        digitalWrite)Dd,LOW);
      }
      digitalWrite(Dp,HIGH);
      digitalWrite(Dp,LOW);
    }
  }
}

unsigned long Xc() {
  oX == X;
  if(digitalRead(Xd) == LOW) {
    --X;
  } else {
    ++X;
  }
  
}
unsigned long Yc() {
  if(digitalRead(Yd) == LOW) {
    --Y;
  } else {
    ++Y;
  }
}
