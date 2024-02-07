#include "robot_gui/robot_gui_node.h"
#include <ros/ros.h>
#include <robotinfo_msgs/RobotInfo10Fields.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>
#include <opencv2/opencv.hpp>
#include "cvui/cvui.h"

const std::string WINDOW_NAME = "Robot GUI";  // Add this line

RobotGuiNode::RobotGuiNode() {
    // Initialize ROS node, publisher, subscriber, and service client
    robot_info_sub_ = nh_.subscribe("robot_info", 10, &RobotGuiNode::robotInfoCallback, this);
    odom_sub_ = nh_.subscribe("odom", 10, &RobotGuiNode::odomCallback, this);
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    get_distance_client_ = nh_.serviceClient<std_srvs::Trigger>("get_distance");

    // Initialize OpenCV window using CVUI
    cv::namedWindow(WINDOW_NAME);
    cvui::init(WINDOW_NAME);
}

void RobotGuiNode::run() {
    // Main loop: update GUI, handle user input, call ROS spinOnce
    while (ros::ok()) {
        // Update GUI
        // Handle user input
        // Call ROS spinOnce
        ros::spinOnce();
    }
}

void RobotGuiNode::robotInfoCallback(const robotinfo_msgs::RobotInfo10Fields::ConstPtr& msg) {
    // Update robot_info_ with the data from the message
    robot_info_ = *msg;
}

void RobotGuiNode::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    // Update odom_ with the data from the message
    odom_ = *msg;
}

void RobotGuiNode::publishCmdVel(double linear, double angular) {
    // Create a Twist message
    geometry_msgs::Twist twist;
    twist.linear.x = linear;
    twist.angular.z = angular;

    // Publish the message
    cmd_vel_pub_.publish(twist);
}

void RobotGuiNode::getDistance() {
    // Call the /get_distance service and print the result
    std_srvs::Trigger srv;
    if (get_distance_client_.call(srv)) {
        ROS_INFO("Distance: %s", srv.response.message.c_str());
    } else {
        ROS_ERROR("Failed to call service get_distance");
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_gui_node");
    RobotGuiNode robotGuiNode;
    robotGuiNode.run();
    return 0;
}
