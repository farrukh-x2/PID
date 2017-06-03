# PID-Controller
From Self-Driving Car Engineer Nanodegree Program


![](PID-Controller.gif)

Overview
---
The goal of this project to implement PID controller in C++. The parameters of PID were tuned to achieve the fastest speed  in the simulator track as shown above.

Two PID controllers were used, one to control the steering of the car and other one to control the throttle of the car

Parameter Tuning
---
Background:
* Proportional Controller: This part of the controller has an immediate effect in proportion to error. For the steering it has a value of 0.0625 and the throttle 0.5. If the value is too high, let's say for steering controller, we would observe the car swerve around.
* Integral Controller: This part adjusts for constant noise or offset of the system. This value is typical low. A high value for steering controller would simply make the car leave the track to one side in the beginning. For steering the value is 0.00174 and for throttle its 0.002.
* Derivative Controller: This part of the controller corrects for the error from the previous state. This way the Proportional controller can have a lower value and the remaining correction is done by the Derivative controller. This leads to smoother steering. For steering controller the value is 2.375 and for speed controller its 10.

For Parameter Tuning, I implemented the twiddle algorithm. Since the twiddle algorithm recursively finds the parameters, it takes a long time to converge especially when each iteration takes up to 30 seconds of driving partially around the track.

Instead I switched to manually tuning. First, I tuned for the steering controller. P and D parameters were trained first. After figuring out the broad range of the values they were narrowed down to maximize the smoothness of the drive. Then the value of I controller was included and tuned.

Afterwards I tuned the parameters for the speed controller using a similar approach.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) - to connect with simulator
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.
