#include <Arduino.h>
#include <math.h>
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

JoystickReading joystick_reading;

JointSpace setpoint;
JointSpace new_setpoint;

double position1 = 0; //radians
double position2 = 0; //radians
double controlEffort1 = 0; //duty cycle
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

double scaledX = 0;
double scaledY = 0;

double alpha = 0.001;

// Checks if provided JointSpace state is within safety limits
// Returns true if it is and false otherwise
bool safetyLimit(JointSpace state) {
    return abs(state.theta1) <= M_PI/2.0 &&
           abs(state.theta2) <= M_PI*0.9 &&
           abs(state.theta1 + state.theta2) <= M_PI/2;
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

            new_setpoint = {scaledX, scaledY};
            new_setpoint = new_setpoint * PI;
        } else {
            // TODO 2: Set new_setpoint using inverseKinematics() on joystick_reading
        }

        // If new setpoint is outside safety limits, use old setpoint so robot does nothing
        if (!safetyLimit(new_setpoint)) {
            new_setpoint = setpoint;
        }

        // Exponential smoothing filter
        setpoint = new_setpoint*alpha + setpoint*(1 - alpha);

        position1 = encoder1.getPosition();
        position2 = encoder2.getPosition();
        controlEffort1 = motorPID.calculateParallel(setpoint.theta1, position1);
        controlEffort2 = motorPID.calculateParallel(setpoint.theta2, position2);

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
                          setpoint.theta1, position1, controlEffort1, averageTimeBetweenPidLoops);
            Serial.printf("MOTOR 2 Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f, Avg Time Between PID Loops (us): %.2f\n",
                          setpoint.theta2, position2, controlEffort2, averageTimeBetweenPidLoops);

            // Reset the accumulator and count for the next set of averages
            timeBetweenPidLoopsAccumulator = 0;
            pidLoopIntervalCount = 1; // Reset to 1 to skip the first loop's interval calculation
        }
    }
}
