#include <Arduino.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "util.h"
#include "MotorDriver.h"
#include "kinematics.h"
#include "joystick.h"

// TODO 2: Change this bool flag to false to use task space
bool JOINT_SPACE = true;

//PID Parameters
double kp = 5;
double ki = 0;
double kd = 0;
double tau = 0.1; //seconds
PID motorPID(kp, ki, kd, 0, tau, false);

double setpoint1 = 0; //radians
double new_setpoint1 = 0;
double position1 = 0; //radians
double controlEffort1 = 0; //duty cycle

double setpoint2 = 0; //radians
double new_setpoint2 = 0;
double position2 = 0; //radians
double controlEffort2 = 0; //duty cycle

MotorDriver motor1(DIR1, PWM1, 0);
MotorDriver motor2(DIR2, PWM2, 0);
EncoderVelocity encoder1(ENCODER1_B_PIN, ENCODER1_A_PIN, CPR_312_RPM, 0.2);
EncoderVelocity encoder2(ENCODER2_B_PIN, ENCODER2_A_PIN, CPR_312_RPM, 0.2);

//variables for calculating the average time between PID loops
unsigned long currentPidLoopStartTime = 0;
unsigned long previousPidLoopStartTime = 0;
unsigned long timeBetweenPidLoopsAccumulator = 0;
int pidLoopIntervalCount = 0;

JoystickReading joystick_reading;

double scaledX = 0;
double scaledY = 0;

double alpha = 0.001;

JointSpace safetyLimit(JointSpace state) {
    return state; 
};

void setup() {
    motor1.setup();
    motor2.setup();

    Serial.begin(); 
    previousPidLoopStartTime = micros(); // Record start time of first PID loop

    setup_joystick();
}

void loop() {
    // Update PID at 10kHz
    EVERY_N_MICROS(100) {        
        currentPidLoopStartTime = micros(); // Record start time of current PID loop

        // Calculate the time between the start of the current and the previous PID loop
        if (pidLoopIntervalCount > 0) { // Skip the first loop to have a previous time to compare
            timeBetweenPidLoopsAccumulator += currentPidLoopStartTime - previousPidLoopStartTime;
        }
        previousPidLoopStartTime = currentPidLoopStartTime; // Update previous start time for the next loop
        pidLoopIntervalCount++;

        // TODO 1: Use the function you implemented in joystick.cpp to read inputs from the joystick 
        // joystick_reading = 

        if (JOINT_SPACE) {
            // TODO 1: Scale joystick_reading to range [-1, 1]
            scaledX = 0;
            scaledY = 0;
            new_setpoint1 = PI*scaledX;
            new_setpoint2 = PI*scaledY;
        } else {
            // TODO 2: Change the setpoints to use inverseKinematics() on joystick_reading
            new_setpoint1 = 0;
            new_setpoint2 = 0;
        }

        // Exponential smoothing filter
        setpoint1 = alpha*new_setpoint1 + (1 - alpha)*setpoint1;
        setpoint2 = alpha*new_setpoint2 + (1 - alpha)*setpoint2;

        position1 = encoder1.getPosition();
        position2 = encoder2.getPosition();
        controlEffort1 = motorPID.calculateParallel(setpoint1, position1);
        controlEffort2 = motorPID.calculateParallel(setpoint2, position2);

        motor1.drive(controlEffort1);
        motor2.drive(controlEffort2);
    }

    // Print values at 10Hz
    EVERY_N_MILLIS(100) {
        if (pidLoopIntervalCount > 1) { // Ensure there's at least one interval to calculate
            // Calculate the average time between PID loop starts
            double averageTimeBetweenPidLoops = (double)timeBetweenPidLoopsAccumulator / (pidLoopIntervalCount - 1);

            // Print values to serial monitor
            Serial.printf("MOTOR 1 Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f, Avg Time Between PID Loops (us): %.2f\n",
                          setpoint1, position1, controlEffort1, averageTimeBetweenPidLoops);
            Serial.printf("MOTOR 2 Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f, Avg Time Between PID Loops (us): %.2f\n",
                          setpoint2, position2, controlEffort2, averageTimeBetweenPidLoops);

            // Reset the accumulator and count for the next set of averages
            timeBetweenPidLoopsAccumulator = 0;
            pidLoopIntervalCount = 1; // Reset to 1 to skip the first loop's interval calculation
        }
    }
}