#include "PID.h"
#include "Servo.h"
#include "constants.h"

//////////////////////////////////////////////////////////////////////////
//                       FUNCTION IMPLEMENTATION                        //
//////////////////////////////////////////////////////////////////////////

void PID::followLine()
{
    int midpoint = m_camera->getMidpoint();

    int error = SET_POINT - m_camera->getMidpoint(); // if positive, the servo should turn right
    int dInput = (midpoint - m_prevMidpoint);  // by doing a difference in inputs, when setpoint changes we don't get a spike in the output

    // calculate angle to turn to proportional to error
    m_turnAngle = MID_ANGLE + (Kp * error) + (Kd * dInput);
    
    // normalize turn angles if they exceed servo max turn angles
    if(m_turnAngle > MAX_TURN_ANGLE)
       m_turnAngle = MAX_TURN_ANGLE;
    if(m_turnAngle < MIN_TURN_ANGLE)
       m_turnAngle = MIN_TURN_ANGLE;

    // return turn angle 
    m_servo->write(m_turnAngle);
     
    // remember variable for next time  
    m_prevMidpoint = midpoint;
}

PID:: PID(Servo* servo, Camera* camera): m_servo(servo), m_camera(camera)
{}

