#include "Arduino.h"
#include "HCSR04.h"

HCSR04::HCSR04(int trigger, int echo)
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    _trigger = trigger;
    _echo = echo;
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

unsigned int HCSR04::distanceInMillimeters()
{
    int duration = echoInMicroseconds();
    
    // Given the speed of sound in air is 332m/s = 3320cm/s = 0.0332cm/us).
    return (duration / 2) * 0.332;
}

void HCSR04::ToSerial()
{
    Serial.print("{");
        Serial.print("\"Protocol\":\"Bifrost\",");
        Serial.print("\"Device\":\"HCSR04\",");
        Serial.print("\"Properties\":{");
            Serial.print("\"Distance\":");
            Serial.print(distanceInMillimeters());
        Serial.print("}");
    Serial.println("}");
}