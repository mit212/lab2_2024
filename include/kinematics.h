#include <math.h>

// TODO: Change the values below to reflect the actual lengths of the links.
# define LINK1 0.169 // m
# define LINK2 0.169 // m

struct JointSpace {
    double theta1; // radians
    double theta2; // radians

    JointSpace operator+(const JointSpace& other) const
    {
        JointSpace result;
        result.theta1 = theta1 + other.theta1;
        result.theta2 = theta2 + other.theta2;
        return result;
    };

    JointSpace operator*(const double& k) const
    {
        JointSpace result;
        result.theta1 = theta1 * k;
        result.theta2 = theta2 * k;
        return result;
    };
};

struct TaskSpace {
    double x; // m 
    double y; // m
};

TaskSpace forwardKinematics(JointSpace state);
JointSpace inverseKinematics(TaskSpace point);