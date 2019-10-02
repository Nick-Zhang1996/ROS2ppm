## ROS 2 PPM Proj
This project developed a system that allows an AVR based Arduino(connected to a PC via USB) to subscribe to rostopics and then generate PPM signal that can be fed to a high frequency module, which acts as a transmitter to control RC cars/planes, etc.

The code is tested on 328p based Arduino Nano, Ubuntu Linux running ROS kinetic, built with catkin tools, using dasmikro ASF tx module to control Kyosho Miniz cars.

## Usage
* Connect a Xbox controller (or equivalent with modification) to computer via USB
* Connect an Arduino, equipped with a PPM high freq module, loaded with firmware supplied, to computer via USB
* `roslaunch ros2ppm demo.launch` will allow a paired mini-z to be driven with the controller

### Build
Before using this package, you should have ROS, catkin tools, rosserial properly installed. 

You also need an catkin workspace initialized by `catkin init` (from catkin tools, not catkin_make suite in ROS.org tutorial)

For more info on catkin tools click [here](https://catkin-tools.readthedocs.io/en/latest/index.html)

#### Host computer side

* Clone this repo, rosserial, and [rcvip_msgs](https://github.com/Nick-Zhang1996/rcvip_msgs) into your `catkin_ws/src/`, set the install flag with `catkin config --install`, then build with `catkin build`
* Source `catkin_ws/install/setup.bash`

#### Arduino side
To compile ros compatible code on Arduino IDE, 

* first generate headers for Arduino IDE, by running `rosrun rosserial_arduino make_libraries.py ~/sketchbook/libraries` assuming `~/sketchbook/libraries` is where your arduino library folder is.
* Compile `ros2ppm_main.ino` with Arduino IDE and upload to Arduino. 
* PPM output is on pin D4

You can setup catkin to automate this build/upload process but it's a lot of work for little benefit in my opinion.

### Running
After rosserial node is up by running `rosrun rosserial_python serial_node.py /dev/ttyUSB0` assuming your arduino shows up on `/dev/ttyUSB0` You should be able to control PPM output from Arduino by publishing to topic `rc_vip/channel` beware of range. It is possible that the requested pulsewidth can't be executed due to restrains in the firmware. 

#### TODO:
* Implement braking and reversing with joystick
* Failsafe
