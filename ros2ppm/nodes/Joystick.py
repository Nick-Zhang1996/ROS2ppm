#!/usr/bin/env python

#drive the car with a joystick
import rospy
from sensor_msgs.msg import Joy
from rcvip_msgs.msg import RCchannel

def mapdata(x,a,b,c,d):
    y=(x-a)/(b-a)*(d-c)+c
    return y

def joystick_callback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    print(data.axes)
    msg = RCchannel()
    msg.header = data.header
    # R knob? 1.0 undepressed, -1 fully depressed
    msg.ch[0] = mapdata(data.axes[5],1.0,-1.0,1000,2000)
    # left joystick? 1.0 left, -1 right
    msg.ch[1] = mapdata(data.axes[0],1.0,-1.0,1000,2000)
    pub.publish(msg)


if __name__ == '__main__':

    rospy.init_node('Joystick2channel', anonymous=False)
    rospy.Subscriber("joy", Joy, joystick_callback)
    pub = rospy.Publisher("vip_rc/channel", RCchannel, queue_size=1)

    rospy.spin()
