#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"
#include "kinematics.h"

#define PRINT_DELAY 30 // Delay between printing to serial in milliseconds

JointSpace state;
JointSpace test_state;
JointSpace alt_test_state;
TaskSpace point;

// Encoder velocity readers
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM);
EncoderVelocity encoder2(ENCODER2_B_PIN, ENCODER2_A_PIN, CPR_60_RPM);

void setup() {
    Serial.begin();
}

//Prints the encoder readings to the serial monitor
void printExpectedJoint(){
    state.theta1 = encoder1.getPosition() + THETA1_OFFSET;
    state.theta2 = -encoder2.getPosition();
    point = forwardKinematics(state);
    test_state = inverseKinematics(point);
    Serial.printf("theta1_error: %.2f, theta2_error: %.2f\n", 
                  abs(state.theta1 - test_state.theta1),
                  abs(state.theta2 - test_state.theta2));
    
    // alt_test_state.theta1 = 2*atan2(point.y, point.x) - test_state.theta1;
    // alt_test_state.theta2 = -test_state.theta2; 

    // Serial.printf("theta1_error: %.2f, theta2_error: %.2f\n", 
    //               min(abs(state.theta1 - test_state.theta1),
    //               abs(state.theta1 - alt_test_state.theta1)),
    //               min(abs(state.theta2 - test_state.theta2),
    //               abs(state.theta2 - alt_test_state.theta2)));
 }

void loop(){
    // Print encoder readings every PRINT_DELAY milliseconds
    EVERY_N_MILLIS(PRINT_DELAY) {
        printExpectedJoint();
    }
}