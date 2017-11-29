#include "Arduino.h"
#include "HCSR04.h"

HCSR04::HCSR04(int trigger, int echo)
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    _trigger = trigger;
    _echo = echo;
}

HCSR04::HCSR04(int trigger, int echo, int minRange, int maxRange)
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    _trigger = trigger;
    _echo = echo;
	_minRange = minRange;
    _maxRange = maxRange;
}

unsigned int HCSR04::echoInMicroseconds()
{
    digitalWrite(_trigger, LOW);
    delayMicroseconds(5);
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);  
    // Why don't I just use? "return pulseIn(_echo, HIGH);"
	// Arduino Primo doesn't have access to pulseIn.
    while(digitalRead(_echo) == LOW);

    int pulseStart = micros();

    while(digitalRead(_echo) == HIGH);

    return micros() - pulseStart;
}

int HCSR04::distanceInMillimeters()
{
    int duration = echoInMicroseconds();
    
    // Given the speed of sound in air is 332m/s = 3320cm/s = 0.0332cm/us).
    int distance = (duration / 2) * 0.332;
	
	if (_minRange == -1 && _maxRange == -1)
	{
		return distance;
	}
	
	if (distance > _minRange && distance < _maxRange)
	{
		return distance;
	}	
	
	return -1;
}

void HCSR04::ToSerial()
{
    Serial.println(ToString());
}

String HCSR04::ToString()
{
    String distanceString = "{\"Protocol\":\"Bifrost\",\"Device\":\"HCSR04\",\"Driver version\":\"2.0.0\",\"Properties\":{\"Distance\":<<DISTANCE>>}}";
    distanceString.replace("<<DISTANCE>>", String(distanceInMillimeters()));

    return distanceString;
}