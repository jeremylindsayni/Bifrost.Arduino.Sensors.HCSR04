# Driver for the HCSR04 Ultrasonic Distance Sensor
A library and example for the HCSR04 distance sensor.

## Example

```c++
#include <hcsr04.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

void setup(){
    Serial.begin(9600);
}

void loop() {

    // Output the distance in mm
	Serial.println(hcsr04.distanceInMillimeters());

    // Output information about the device, driver, and distance in Bifrost JSON format
    Serial.println(hcsr04.ToString());

    delay(250);
}
```
