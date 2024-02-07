#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from tf.transformations import euler_from_quaternion
import math

class RotateService(object):
    def __init__(self):
        self._cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        self._odom_sub = None
        self._rotate_service = rospy.Service('/rotate_robot', Rotate, self.handle_rotate_robot)
        self._current_angle = 0.0

    def odom_callback(self, msg):
        orientation_q = msg.pose.pose.orientation
        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, self._current_angle = euler_from_quaternion(orientation_list)
        self._current_angle = math.degrees(self._current_angle)
        self._current_angle = (self._current_angle + 180) % 360 - 180

    def handle_rotate_robot(self, req):
        self._odom_sub = rospy.Subscriber('/odom', Odometry, self.odom_callback)
        target_angle = req.degrees
        rate = rospy.Rate(10)
        vel_msg = Twist()

        while abs(target_angle - self._current_angle) > 0.1:
            if target_angle > self._current_angle:
                vel_msg.angular.z = 0.1
            else:
                vel_msg.angular.z = -0.1
            self._cmd_vel_pub.publish(vel_msg)
            rate.sleep()

        vel_msg.angular.z = 0.0
        self._cmd_vel_pub.publish(vel_msg)
        self._odom_sub.unregister()
        self._odom_sub = None

        return RotateResponse("Rotation completed successfully")

if __name__ == "__main__":
    rospy.init_node('rotate_service_server')
    rotate_service = RotateService()
    rospy.spin()
