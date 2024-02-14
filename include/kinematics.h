#include <math.h>

// TODO: Change the values below to reflect the actual lengths of the links.
# define LINK1 0 
# define LINK2 0

struct State {
    double theta1;
    double theta2;
};

struct Point {
    double x;
    double y;
};

State inverseKinematics(Point endEffector);