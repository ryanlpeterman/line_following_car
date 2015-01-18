//////////////////////////////////////////////////////////////////////////
//                       TODO                                           //
//////////////////////////////////////////////////////////////////////////

//1. potentially only read in half the data values so that the processing is faster
//2. discard first 14 pixels and last 14 pixels because of bad reading on edges and less data to process

//////////////////////////////////////////////////////////////////////////
//                       SETUP                                          //
//////////////////////////////////////////////////////////////////////////

// include header files
#include "camera.h"
#include "PID.h"
#include "constants.h"
#include "Servo.h"

  // instance declarations
  Servo my_servo;
  Camera my_camera;
  PID my_PID(&my_servo, &my_camera);

void setup()
{ 
  my_servo.attach(servoPin);
  pinMode(analogOutput, INPUT);
  pinMode(clock, OUTPUT);
  pinMode(initializeScan, OUTPUT);
  pinMode(motorDriver, OUTPUT);

  Serial.begin(9600);

  int beginTime = millis();
}

//////////////////////////////////////////////////////////////////////////
//                       MAIN LOOP                                      //
//////////////////////////////////////////////////////////////////////////

void loop()
{
    // Begin exposure and determine midpoint
    my_camera.cameraRead();
    my_camera.cameraPrint();
    my_camera.detectLine();

    // PID Servo controller
    my_PID.followLine();
    
    // Motor Control
    int turnMagnitude = abs(my_PID.getTurnAngle() - MID_ANGLE);
    int PWM = map(turnMagnitude, 0, 35, 40, 100);
    analogWrite(motorDriver, PWM);

    // Exposure Time
    delay(20);

}


