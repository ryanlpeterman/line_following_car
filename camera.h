#ifndef CAMERA_INCLUDED
#define CAMERA_INCLUDED

#include <arduino.h>

//////////////////////////////////////////////////////////////////////////
//                       FUNCTION PROTOTYPES                            //
//////////////////////////////////////////////////////////////////////////

class Camera
{
  public:
    Camera();
    void cameraRead();                          // reads the pixel values and stores them in pixelArray
    void detectLine();                          // detects the line and outputs asterisk in interpreted middle of line
    void cameraPrint();                         // formats data to single digits and outputs human readable data
    boolean isEdge(int index);                  // checks if the index is the edge of line; checks at index in direction of dir(true = forward, false backward)
    int calcDeriv(int first, int second);       //returns abs derivative given two indexes (second - first)
    int getMidpoint(){return m_midpoint;};      //returns midpoint so functions outside class can access
    
  private:
    int m_pixelArray[128];    // Pixel array that holds values
    int m_midpoint;           // holds the last perceived midpoint
};
#endif
