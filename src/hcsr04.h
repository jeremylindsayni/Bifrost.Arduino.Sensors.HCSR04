#ifndef HCSR04_h
#define HCSR04_h

#include "Arduino.h"

class HCSR04
{
  public:
    HCSR04(int trigger, int echo);
	HCSR04(int trigger, int echo, int minRange, int maxRange);
    unsigned int echoInMicroseconds();
    int distanceInMillimeters();
    void ToSerial();
    String ToString();
  private:
    int _trigger;
    int _echo;
	int _minRange = -1;
	int _maxRange = -1;
};

#endif