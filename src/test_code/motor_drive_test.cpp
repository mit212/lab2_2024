#include <Arduino.h>
#include "pinout.h"
#include "MotorDriver.h"

#define DELAY 200 // Delay between motor movements in milliseconds


// Create an instance of the MotorDriver class
MotorDriver motor1(DIR1, PWM1, 0);
MotorDriver motor2(DIR2, PWM2, 0);

void setup() {
    // Initialize serial communication
    Serial.begin();

    // Setup the motor driver
    motor1.setup();
    motor2.setup();
}

void test_motor(MotorDriver motor) {
    // Move the motor forward at full speed
    Serial.println("Moving Forward at full speed");
    motor.drive(1.0); // 100% duty cycle
    delay(DELAY);

    // Stop the motor
    Serial.println("Stopping");
    motor.drive(0.0); // 0% duty cycle
    delay(DELAY);

    // Move the motor forward at half speed
    Serial.println("Moving Forward at half speed");
    motor.drive(0.5); // 50% duty cycle
    delay(DELAY);

    // Stop the motor
    Serial.println("Stopping");
    motor.drive(0.0); // 0% duty cycle
    delay(DELAY);

    // Move the motor backward at full speed
    Serial.println("Moving Backward at full speed");
    motor.drive(-1.0); // -100% duty cycle (backward)
    delay(DELAY);

    // Stop the motor
    Serial.println("Stopping");
    motor.drive(0.0); // 0% duty cycle
    delay(DELAY);

    // Move the motor backward at half speed
    Serial.println("Moving Backward at half speed");
    motor.drive(-0.5); // -50% duty cycle (backward)
    delay(DELAY);

    // Stop the motor
    Serial.println("Stopping");
    motor.drive(0.0); // 0% duty cycle
    delay(DELAY);
}

void loop() {
    test_motor(motor1);
    test_motor(motor2);
}
