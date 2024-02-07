#ifndef ROBOT_GUI_ROBOT_GUI_NODE_H
#define ROBOT_GUI_ROBOT_GUI_NODE_H

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>
#include "robotinfo_msgs/RobotInfo10Fields.h"

class RobotGuiNode {
public:
    RobotGuiNode();
    void run();

private:
    void robotInfoCallback(const robotinfo_msgs::RobotInfo10Fields::ConstPtr& msg);
    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
    void publishCmdVel(double linear, double angular);
    void getDistance();

    ros::NodeHandle nh_;
    ros::Subscriber robot_info_sub_;
    ros::Subscriber odom_sub_;
    ros::Publisher cmd_vel_pub_;
    ros::ServiceClient get_distance_client_;

    // Variables to store the data received from the callbacks
    robotinfo_msgs::RobotInfo10Fields robot_info_;
    nav_msgs::Odometry odom_;
};

#endif  // ROBOT_GUI_ROBOT_GUI_NODE_H
