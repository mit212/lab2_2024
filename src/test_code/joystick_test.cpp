#include <Arduino.h>
#include "pinout.h"
// TODO: Add an #include to refer to joystick.h.

// TODO: Modify the two lines below to use the JoystickReading struct.
int X = 0;
int Y = 0;

void setup() {
    Serial.begin();

    // TODO: Modify the two lines below to use a function you implemented in joystick.cpp
    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
}

void loop() {
    // TODO: Modify the three lines below to use a function you implemented in joystick.cpp
    X = analogRead(XPIN);
    Y = analogRead(YPIN);
    Serial.printf("X: %d, Y: %d\n", X, Y);
    
    delay(50);
}
