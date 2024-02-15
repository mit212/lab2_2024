#ifndef JOYSTICK
#define JOYSTICK

#include "pinout.h"

struct JoystickReading {
    // TODO: Define your struct here.
};

void setupJoystick();
JoystickReading readJoystick();

#endif