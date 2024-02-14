#include "kinematics.h"

TaskSpace forwardKinematics(JointSpace state) {
    // Initializes a State variable called command
    TaskSpace point; 

    // TODO: Modify the two lines below to use the forward kinematics equations you derived. 
    // You may need the variables: LINK1, LINK2, state
    // as well as the functions: double cos(double x), double sin(double x), double tan(double x).
    // These functions take in a double representing the angle in radians and return a double.
    point.x = 0;
    point.y = 0;

    return point;
}

JointSpace inverseKinematics(TaskSpace point) {
    // Initializes a State variable called command
    JointSpace state; 

    // TODO: Modify the two lines below to use the inverse kinematics equations you derived. 
    // You may need the variables: LINK1, LINK2, point
    // as well as the functions: double acos(double x), double asin(double x), double atan(double x).
    // These functions take in a double and return a double representing the angle in radians.
    // state.theta1 and state.theta2 should be in the range [-pi/2, pi/2].
    state.theta1 = 0;
    state.theta2 = 0;

    return state;
}