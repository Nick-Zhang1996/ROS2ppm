## ROS 2 PPM Proj
This project aims to develop a firmware that allows an AVR based Arduino(connected to a PC via USB) to subscribe to rostopics and then generate RC compatible PPM signal that can be fed to a high frequency module, which acts as a transmitter to control RC cars/planes, etc.

The code is tested on 328p based Arduino Nano, Ubuntu Linux running ROS kinetic, built with catkin tools, using dasmikro ASF compatible tx module to control Kyosho Miniz cars.

## Usage
Before using this package, you should have ROS, catkin tools, rosserial properly installed. 
You also need an catkin workspace initialized by `catkin init` (from catkin tools, not catkin_make suite in ROS.org tutorial)
For more info on catkin tools click [here](https://catkin-tools.readthedocs.io/en/latest/index.html)

Clone this repo into your `catkin_ws/src/`, build with `catkin config --install`, then `catkin build`
Source `catkin_ws/install/setup.bash`
Generate headers for Arduino IDE, by running `rosrun rosserial_client make_libraries ~/sketchbook/libraries` assuming `~/sketchbook/libraries` is where your arduino library folder is.
Compile `ros2ppm_main.ino` with Arduino IDE and upload to Arduino. 
You can setup catkin to automate this build/upload process but it's a lot of work for little benefit in my opinion.

#### TODO:
* Put TK18 PPM on scope, record critical values
* Draw PPM illustration, explain PPM graphically
* Write ROS package
* [importent] write ROS package install tutorial [done]
* ROS -> Arduino (rosserial_arduino) implementation
* Testing
