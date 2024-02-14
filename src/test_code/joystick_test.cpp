#include <Arduino.h>
#include "pinout.h"
// TODO: Add an #include here to refer to joystick.h.

// TODO: Update the two lines below to use the struct instead of two ints.
int X = 0;
int Y = 0;

void setup() {
    Serial.begin();

    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
}

void loop() {
    // TODO: Update the three lines below to use the struct.
    X = analogRead(XPIN);
    Y = analogRead(YPIN);
    Serial.printf("X: %d, Y: %d\n", X, Y);
    delay(50);
}
