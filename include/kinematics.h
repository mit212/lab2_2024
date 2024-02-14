#include <math.h>

// TODO: Change the values below to reflect the actual lengths of the links.
# define LINK1 0 
# define LINK2 0

struct JointSpace {
    double theta1;
    double theta2;
};

struct TaskSpace {
    double x;
    double y;
};

TaskSpace forwardKinematics(JointSpace state);
JointSpace inverseKinematics(TaskSpace point);