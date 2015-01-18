#ifndef PID_INCLUDED
#define PID_INCLUDED

#include <arduino.h>
#include <camera.h>
#include <Servo.h>

//////////////////////////////////////////////////////////////////////////
//                       FUNCTION PROTOTYPES                            //
//////////////////////////////////////////////////////////////////////////
class Servo;

class PID
{
  public:
      PID(Servo* servo, Camera* camera); 		// constructor
      void followLine();                 		// takes in the last perceived midpoint and fixes error
      int getTurnAngle(){return m_turnAngle;};  //returns turn angle for access outside of class
  private:
      int m_turnAngle;                   		// holds value of how much servo should turn by
      int m_previousAngle;               		// holds value of how much servo last turned by
      int m_prevMidpoint;                		// holds value of previous midpoint input
      Servo* m_servo;
      Camera* m_camera;
};


#endif
