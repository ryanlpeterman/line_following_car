#include "camera.h"
#include "constants.h"

//////////////////////////////////////////////////////////////////////////
//                       FUNCTION IMPLEMENTATION                        //
//////////////////////////////////////////////////////////////////////////

Camera::Camera()
{
  for(int i = 0; i < 128; i++)
  {
    m_pixelArray[i] = 0; 
  }
}

int Camera::calcDeriv(int first, int second)
{
  return m_pixelArray[second] - m_pixelArray[first];
}

boolean Camera::isEdge(int index)
{
  int derivative = 0;   //stores difference between pixel values incrementing
  
  // calculate derivative around the index
  for(int i = -2; i < 3; i++)
  {
     derivative += calcDeriv(index + i, index + 1 + i);
  }
  
  //if the average change is sufficiently large, it is an edge
  if(abs(derivative)/5 > 35)
  {
    return true; 
  }
  
  // else, the candidate for edge was noise
  return false;
}

void Camera::detectLine()
{
  int derivative = 0;                  //stores difference between pixel values incrementing from front
  int beginIndex = -1;                  //stores begining index of the line
  int endIndex = 128;                    //stores ending index of the line               
  
  for(int i = 0; i < 127; i++)
  {
    //calculating deriv from the front
    derivative = calcDeriv(i, i + 1); 
    
    // if difference between pixel values spikes and is an edge then we found front edge
    if(derivative > 70 && isEdge(i))
    {
      // initial spike derivative and then leveled off thus we can now set beginIndex
      beginIndex = i;
    }
    
    //calculating deriv from the back
    derivative = calcDeriv(127 - i, 126 - i);
    
    // if difference between pixel values spikes and is an edge then we found back edge
    if(derivative > 70 && isEdge(127 - i))
    {
      // initial spike derivative and then leveled off thus we can now set endIndex
      endIndex = 127 - i;
    }
    
    // both indexes have been found break to save time
    if(beginIndex != -1 && endIndex != 128)
    {
      break;
    }
  }
  
  // valid indexes not found don't print asterisk
  if(beginIndex == -1 && endIndex == 128)
  {
     return;
  }

   m_midpoint = (endIndex + beginIndex)/2; //stores calculated midpoint index of line

// TEST LOOP PRINTS OUT VALUES FOR DEBUGGING

  //outputs spaces before the position of midpoint
  for(int i = 0; i < 127; i++)
  {
    if(i == beginIndex)
      Serial.print("L");
    else if (i == m_midpoint)
      Serial.print("*");
    else if(i == endIndex)
      Serial.print("R");
    else
      Serial.print(" "); 
  }
  
  Serial.println(" ");
}

void Camera::cameraRead()
{
  // initialization pulse
  digitalWrite(initializeScan, HIGH);
  digitalWrite(clock, HIGH);
  digitalWrite(initializeScan, LOW);
  digitalWrite(clock, LOW);
  
  // clock pulses and data aquisition
  for(int i = 0; i < 128; i++)
  {
    digitalWrite(clock, HIGH);
    m_pixelArray[i] = analogRead(analogOutput);
    digitalWrite(clock, LOW);
  }
}

void Camera::cameraPrint()
{
  for(int i = 0; i < 128; i++)
  {
    Serial.print(int(m_pixelArray[i]*(9./1023)));
  }
  
  // for readability
  Serial.println(" ");
}
