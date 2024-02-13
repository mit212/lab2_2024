# Lab 2: 2-DoF Robot

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

## Table of Contents
- [Lab 1: 2-DoF Robot](#lab-2-2-dof-robot)
  - [Table of Contents](#table-of-contents)  
    
## 1 Hardware Assembly

### 1.1 Nuts and Bolts

This section should take 30 mins or under. Include pics and such.

### 1.2 Wiring Motors 

Explicit instructions.
Connect to rails.

## 1.3 Validating the Motor 

Run some code to actuate the motors a little back and forth.

CHECKOFF - MOTOR

## 1.4 Wire Encoder

## 1.5 Validating the Encoder 

Then run some other code to check the encoder reads on serial monitor.


## 2 Connecting Joystick


### 2.1 Wiring Joystick

### 2.2 Joystick Input

Use this joystick input code we gave. Try it out. Examine to learn the diff sections if you havent yet.

modify so that uses struct.

## 3 Controlling the Robot via Joystick

### 3.1 Joint Space

Write your own code to control motor 1 and motor 2 using the 2 axis.


### 3.2 Alpha-Based Low Pass Filter

try it again with filtering, should be smoother

### 3.3 Draw Something

its probably going to be bad


CHECKOFF?

### 3.4 Inverse Kinematics

Derive kinematics equations then use that to derive inverse kinematics.

### 3.5 Cartesian Space

Copy the code to new file. Modify so that x y in world coords correspond to joystick 2 axis.

### 3.6 Draw Something Again

Use joystick to draw something fun!


| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate  to a TA or LA! |

## 4 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback and present the completion screen to a TA or LA. 

## X Optional

### X.1 PID Tune?

Change the gains so that it moves smoothly. 

### X.2 Set a Path (Circle?)

Make copy of your code and modify so that it will auto follow a set path, like a circle.

### X.3 Wireless?

Rewire to make joystick wireless from the rest of the system!

| :white_check_mark: OPTIONAL CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate your awesome wireless joystick to a TA or LA! |



[^1]: Version 1 - 2024: Jinger Chong
