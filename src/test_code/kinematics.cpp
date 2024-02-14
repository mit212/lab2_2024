#include "kinematics.h"

State inverseKinematics(Point endEffector) {
    // Initializes a State variable called command
    State command; 

    // TODO: Modify the two lines below to use the inverse kinematics equations you derived. 
    // You may need the variables: LINK1, LINK2, endEffector
    // as well as the functions: double acos(double x), double asin(double x), double atan(double x).
    // These functions take in a double and return a double representing the angle in radians.
    // command.theta1 and command.theta2 should be in the range ???
    command.theta1 = 0;
    command.theta2 = 0;

    return command;
}