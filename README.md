## ROS 2 PPM Proj
This project aims to develop a firmware that allows an AVR based Arduino(connected to a PC via USB) to subscribe to rostopics and then generate RC compatible PPM signal that can be fed to a high frequency module, which acts as a transmitter to control RC cars/planes, etc.

The code is tested on 328p based Arduino Nano, Ubuntu Linux running ROS (version?), Using (high freq module?) to control Kyosho Miniz cars with ASF protocol.

#### TODO:
* Put TK18 PPM on scope, record critical values
* Draw PPM illustration
* Write ROS package
* [importent] write ROS package install tutorial
* ROS -> Arduino (rosserial_arduino) implementation
* Testing
