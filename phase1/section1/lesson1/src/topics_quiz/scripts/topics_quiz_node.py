#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan

def callback(msg):
    global pub
    twist = Twist()
    
    # Front laser reading
    front_range = msg.ranges[len(msg.ranges)//2]
    
    # Right and left side laser readings
    right_range = msg.ranges[0]
    left_range = msg.ranges[-1]
    
    if front_range > 1:
        twist.linear.x = 0.5
    elif front_range < 1 or right_range < 1:
        twist.angular.z = 0.5
    elif left_range < 1:
        twist.angular.z = -0.5

    pub.publish(twist)

rospy.init_node('topics_quiz_node')
sub = rospy.Subscriber('/kobuki/laser/scan', LaserScan, callback)
pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
rospy.spin()
