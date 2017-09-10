#ifndef HCSR04_h
#define HCSR04_h

#include "Arduino.h"

class HCSR04
{
  public:
    HCSR04(int trigger, int echo);
    unsigned int echoInMicroseconds();
    unsigned int distanceInMillimeters();
    void ToSerial();
    String ToString();
  private:
    int _trigger;
    int _echo;
};

#endif