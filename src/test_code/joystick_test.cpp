#include <Arduino.h>
#include "pinout.h"

int X = 0;
int Y = 0;

void setup() {
    Serial.begin();

    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
}

void loop() {
    X = analogRead(XPIN);
    Y = analogRead(YPIN);
    Serial.printf("X: %d, Y: %d\n", X, Y);
    delay(50);
}
