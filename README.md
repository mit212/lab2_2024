# Lab 2: 2-DoF Robot

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [1 Hardware Assembly](#1-hardware-assembly)
- [2 Wiring and Validation](#2-wiring-and-validation)
- [3 Adding the Joystick](#3-adding-the-joystick)
- [4 Controlling the Robot via Joystick](#4-controlling-the-robot-via-joystick)
  - [4.1 Joint Space](#41-joint-space)
  - [4.2 Draw Something](#42-draw-something)
  - [4.3 Forward Kinematics](#43-forward-kinematics)
  - [4.4 Inverse Kinematics](#44-inverse-kinematics)
  - [4.5 Cartesian Space](#45-cartesian-space)
  - [4.6 Draw Something Pt.2](#46-draw-something-pt2)
- [5 Feedback Form](#5-feedback-form)
- [X Optional](#x-optional)
  - [X.1 PID Tuning](#x1-pid-tuning)
  - [X.2 Setpoint Path](#x2-setpoint-path)
  - [X.3 Make it Wireless](#x3-make-it-wireless)
    
## 1 Hardware Assembly

Below is an image of the 2-DoF robot arm you will assemble. Completing this section should take less than 30 minutes, so please ask for help if you feel like you are taking longer! We want you to have enough time to complete the remaining sections.

<p align=center>
  <img src=./.images/0_full.png width=500>
</p>

Materials:

- 2 [arm links (low-side U-channel)](https://www.gobilda.com/1143-series-mini-low-side-u-channel-8-hole-216mm-length/)
- 3 [base mounts (U-channel)](https://www.gobilda.com/1120-series-u-channel-4-hole-120mm-length/)
- 2 [motors (60 RPM)](https://www.gobilda.com/5203-series-yellow-jacket-planetary-gear-motor-99-5-1-ratio-24mm-length-8mm-rex-shaft-60-rpm-3-3-5v-encoder/)
- 2 [hubs](https://www.gobilda.com/1310-series-hyper-hub-8mm-rex-bore/)
- [socket head bolts (M4)](https://www.gobilda.com/2800-series-zinc-plated-steel-socket-head-screw-m4-x-0-7mm-8mm-length-25-pack/)
- [hex nuts (M4)](https://www.gobilda.com/2811-series-zinc-plated-steel-hex-nut-m4-x-0-7mm-7mm-hex-25-pack/)
- purple marker holder

Steps:
1. Attach the 2 motors on either end of a single arm link.
    <p align=center>
      <img src=./.images/1_motors.png width=500>
    </p>

2. Add the hubs onto each shaft using 2 set screws.
    <p align=center>
      <img src=./.images/2_hub.png width=500>
    </p>

3. Build the base using 3 U-channels.
    <p align=center>
      <img src=./.images/3_base.png width=500>
    </p>

4. Attach the base to one of the hubs.
    <p align=center>
      <img src=./.images/4_attach.png width=500>
    </p>

5. Attach a new arm to the other hub and attach the marker holder to the end of that arm.
    <p align=center>
      <img src=./.images/5_holder.png width=500>
    </p>

## 2 Wiring and Validation 

Similar to Lab 1, we also need to wire and validate the microcontroller, motors, and encoders.

1. Plug the microcontroller in the breadboard so that the USB-C port is near the edge of the breadboard.
2. Use solid wires to connect the `3.3V` to both `+` rails and `GND` to both `-` rails.
   
    <details>
    <summary><i> What is a rail?</i>
    </summary>

    Rails on a breadboard refer to the two long strips labeled `+` and `-` on either side. They are typically located between red and blue lines parallel to the rails.
    </details>
3. Open `include/pinout.h` and note down the motor and encoder pin numbers.
4. Wire the motors according to the schematic below.

5. Run `motor_drive_test.cpp`. You should see both motors turn in both directions at two different speeds.

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate `motor_drive_test.cpp` to a TA or LA! |

6. Wire the encoders according to the schematic below.
   
7. Run `encoder_basic_test.cpp` and open the Serial Monitor. The count should increase when turning counter-clockwise and decrease when turning clockwise.

**DO WE NEED encoder_test too? is basic test not enough?**

## 3 Adding the Joystick

Now that we have a validated 2-DoF robot, let's add a joystick to control it.

1. Wire the joystick according to the schematic below.
2. To validate that you can read the joystick input, run `joystick_test.cpp` and open your Serial Monitor. You should see joystick readings in the range `[0, 4096)`.

**CHANGE TO STRUCT?**

## 4 Controlling the Robot via Joystick

With the joystick in place, we can then use code to connect the joystick reading to the robot motion.

### 4.1 Joint Space

**DO WE NOT WANT THEM TO CODE? IF THEY DO CODE, OPPORTUNITY TO GIT PUSH?**

Run `motor_position_control.cpp` to control motor 1 and motor 2 in joint space. At a high level, this file:
- reads the joystick
- scales the joystick reading from `[0, 4096)` to `[-1, 1)`
- feeds the joystick reading to a position setpoint
- smoothes the position setpoint using exponential smoothing
- drives the motor using a PID controller

Simply put, the x-axis of the joystick controls the velocity of motor 1, and the y-axis of the joystick controls the velocity of motor 2. This is joint space!

### 4.2 Draw Something
Attach a marker to the end of your 2-DoF arm and try drawing something on your whiteboard using joint space control.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your work of art to a TA or LA! |

### 4.3 Forward Kinematics

First, **derive the forward kinematic equations for a 2-DoF arm**. In other words, derive equations for `x` and `y` in terms of <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code>.

<p align="center">
<img src="./.images/2dofarm.png" alt="drawing" width="300"/>
</p>

<details>
<summary><i> What is forward kinematics? </i></summary>

Put simply, forward kinematics answers the question, "Given the angles of the robot's joints, what are the x, y coordinates of the robot's hand?" For more, refer to lecture 2!

</details>

### 4.4 Inverse Kinematics

Using the forward kinematic equations you found, **derive the inverse kinematic equations for a 2-DoF arm**. In other words, derive equations for <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code> in terms of `x` and `y`.

<details>
<summary><i> What is inverse kinematics? </i></summary>

It's the opposite of forward kinematics!
Put simply, forward inverse kinematics answers the question, "Given the desired x,y coordinates of the robot's hand, what should the angles of the robot's joints be?" For more, refer to lecture 2!

</details>

### 4.5 Cartesian Space

Change `new_setpoint1` and `new_setpoint2` in `motor_position_control.cpp` from joint space to Cartesian space using inverse kinematics.

Hint: Measure the links on your robot.

### 4.6 Draw Something Pt.2

Use the joystick to try draw something fun!

| :white_check_mark: CHECKOFF 3 :white_check_mark:   |
|:---------------------------------------------------|
| Show your (hopefully improved) work of art to a TA or LA! |

## 5 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback and present the completion screen to a TA or LA. 

## X Optional

If you finished lab early, here's a few optional challenges you can try (in any order)!

### X.1 PID Tuning

Change the gains so that it moves smoothly. 

### X.2 Setpoint Path

Make copy of `motor_position_control.cpp` and modify it so that the end-effector of your robot follows a set path, e.g. a circle.

### X.3 Make it Wireless

Ask the staff for some extra parts. Rewire to make joystick wireless from the rest of the system. Afterwards, write code to make your microcontrollers communicate wirelessly.



[^1]: Version 1 - 2024: Jinger Chong, Josh Sohn
