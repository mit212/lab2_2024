# Lab 2: 2-DoF Robot

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [1 Hardware Assembly](#1-hardware-assembly)
- [2 Wiring and Validation](#2-wiring-and-validation)
- [3 Adding the Joystick](#3-adding-the-joystick)
- [4 Moving in Joint Space](#4-moving-in-joint-space)
  - [4.1 Refactoring Code](#41-refactoring-code)
  - [4.2 Commanding the Robot](#42-commanding-the-robot)
  - [4.3 Draw Something](#43-draw-something)
- [5 Moving in Cartesian Space](#5-moving-in-cartesian-space)
  - [5.1 Forward Kinematics](#51-forward-kinematics)
  - [5.2 Inverse Kinematics](#52-inverse-kinematics)
  - [5.3 Commanding the Robot](#53-commanding-the-robot)
  - [5.4 Draw Something Pt.2](#54-draw-something-pt2)
- [6 Git Push](#6-git-push)
- [7 Feedback Form](#7-feedback-form)
- [X Optional](#x-optional)
  - [X.1 PID Tuning](#x1-pid-tuning)
  - [X.2 Setpoint Path](#x2-setpoint-path)
  - [X.3 Make it Wireless](#x3-make-it-wireless)
    
## 1 Hardware Assembly

Below is an image of the 2-DoF robot arm you will assemble. Completing this section should take less than 30 minutes, so please ask for help if you feel like you are taking longer! We want you to have enough time to complete the remaining sections.

<p align=center>
  <img src=./.images/0_full.png width=600>
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
      <img src=./.images/1_motors.png width=400>
    </p>

2. Add the hubs onto each shaft using 2 set screws.
    <p align=center>
      <img src=./.images/2_hub.png width=350>
    </p>

3. Attach the base made of 3 U-channels to one of the hubs.
    <p align=center>
      <img src=./.images/3_attach.png width=300>
    </p>

4. Attach a new arm to the other hub and attach the marker holder to the end of that arm.
    <p align=center>
      <img src=./.images/4_holder.png width=600>
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
    <p align=center>
      <img src=./.images/schematic1.png width=600>
    </p>
5. Push and hold the `M1A`, `M1B`, `M2A`, `M2B` buttons on the motor driver one at a time to check that the motors can spin in both directions.
6. Run `motor_drive_test.cpp`. You should see both motors turn in both directions at two different speeds.

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate `motor_drive_test.cpp` to a TA or LA! |

6. Wire the encoders according to the schematic below.
   <p align=center>
      <img src=./.images/schematic2.png width=800>
    </p>
7. Run `encoder_basic_test.cpp` and open the Serial Monitor. The count should increase when turning counter-clockwise and decrease when turning clockwise.
8. Run `encoder_test.cpp`. Confirm that the position and velocity values are reasonable.


## 3 Adding the Joystick

Now that we have a validated 2-DoF robot, let's add a joystick to control it.

1. Wire the joystick according to the schematic below.
    <p align=center>
      <img src=./.images/schematic3.png width=900>
    </p>
2. To validate that you can read the joystick input, run `joystick_test.cpp` and open the Serial Monitor. You should see joystick readings in the range `[0, 4096).

## 4 Moving in Joint Space

With the joystick in place, we can then use code to connect the joystick reading to the robot motion.

### 4.1 Refactoring Code

1. Open `include/joystick.h` and define a `struct` to store the `x` and `y` values of a joystick reading.
    <details>
    <summary>  <i> What is a struct?</i></summary>

    A structure or `struct` is a user-defined data type that can group *members* of possibly different types into a single type. An example usage is shown below.
    ``` 
    struct Student {
      int id;
      float gpa;
    };

    Student bob(1, 2.0); // Initializes a Student variable called bob with id 1 and gpa 2.0
    bob.gpa = 2.3; // Updates the gpa member of bob to 2.3
    Serial.printf("GPA: %.2f\n", bob.gpa); // Prints the new gpa 2.3 in the Serial Monitor
    ```
    </details>

2. Open `joystick_test.cpp` and modify the code so that `X` and `Y` are stored in your newly-defined `struct` instead of two separate `int`s. 
3. Run `joystick_test.cpp` and open the Serial Monitor. Confirm that your joystick readings are the same as before.
    
### 4.2 Commanding the Robot

Open `motor_position_control.cpp` and complete the `TODO`s. At a high level, the code should do the following:
   - reads the joystick
   - scales the joystick reading from `[0, 4096)` to `[-1, 1)`
   - feeds the joystick reading to a position setpoint
   - smoothes the position setpoint using exponential smoothing
   - drives the motor using a PID controller

Simply put, the x-axis of the joystick controls the velocity of motor 1 and the y-axis of the joystick controls the velocity of motor 2. This is joint space!

### 4.3 Draw Something
Attach a marker to the end of your 2-DoF robot and try drawing something on your whiteboard.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your work of art to a TA or LA! |

## 5 Moving in Cartesian Space

You may have noticed that it is quite difficult to draw something by controlling the motors individually. Since our desired output is in Cartesian space, we can use what we learned in lecture to command the robot in Cartesian space instead of joint space!

### 5.1 Forward Kinematics

First, derive the forward kinematic equations for a 2-DoF arm. In other words, derive equations for `x` and `y` in terms of <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code>.

<p align="center">
<img src="./.images/2dofarm.png" alt="drawing" width="300"/>
</p>

<details>
<summary><i> What is forward kinematics? </i></summary>

Forward kinematics answers the question, "Given the angles of the robot's joints, what are the x, y coordinates of the robot's hand?" For more, refer to lecture 2!

</details>

### 5.2 Inverse Kinematics

Using the forward kinematic equations you found, derive the inverse kinematic equations for a 2-DoF arm. In other words, derive equations for <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code> in terms of `x` and `y`.

<details>
<summary><i> What is inverse kinematics? </i></summary>

It's the opposite of forward kinematics!
Put simply, forward inverse kinematics answers the question, "Given the desired x,y coordinates of the robot's hand, what should the angles of the robot's joints be?" For more, refer to lecture 2!

</details>

Then, translate your derived equations into code by completing the `TODO`s in `include/kinematics.h` and `kinematics.cpp`.

**CONSIDER WRITING TESTS?**

### 5.3 Commanding the Robot

Change `new_setpoint1` and `new_setpoint2` in `motor_position_control.cpp` from joint space to Cartesian space using `State inverseKinematics(Point endEffector)`.

### 5.4 Draw Something Pt.2

Finally, use the joystick to draw something fun!

| :white_check_mark: CHECKOFF 3 :white_check_mark:   |
|:---------------------------------------------------|
| Show your (hopefully improved) work of art to a TA or LA! |

## 6 Git Push

Your new code can currently only be accessed locally. etc etc WIP

## 7 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback and present the completion screen to a TA or LA. 

## X Optional

If you finished lab early, here's a few optional challenges you can try (in any order)!

### X.1 PID Tuning

Change the gains in  `motor_position_control.cpp` so that robot moves smoothly. 

### X.2 Setpoint Path

Make copy of `motor_position_control.cpp` and modify it so that the end-effector of your robot follows a set path, e.g. a circle.

### X.3 Make it Wireless

Ask the staff for some extra parts. Rewire to make joystick wireless from the rest of the system. Afterwards, write code to make your microcontrollers communicate wirelessly. 


[^1]: Version 1 - 2024: Jinger Chong, Josh Sohn
