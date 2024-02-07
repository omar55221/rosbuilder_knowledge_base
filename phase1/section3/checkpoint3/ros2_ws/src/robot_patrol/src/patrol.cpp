#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <vector>
#include <algorithm>

class Patrol : public rclcpp::Node {
public:
    Patrol() : Node("patrol") {
        // Initialize subscriber to the laser scan topic
        laser_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&Patrol::laserCallback, this, std::placeholders::_1));

        // Initialize publisher to the cmd_vel topic
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        // Initialize the control loop timer
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100), // 10 Hz
            std::bind(&Patrol::controlLoop, this));
    }

private:
    void laserCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
        // Find the largest distance in the 180-degree front area
        int start_index = msg->ranges.size() * 1/4; // Starting at -45 degrees
        int end_index = msg->ranges.size() * 3/4; // Ending at 45 degrees

        auto max_it = std::max_element(msg->ranges.begin() + start_index, msg->ranges.begin() + end_index);
        float max_distance = *max_it;
        int max_index = std::distance(msg->ranges.begin(), max_it);
        float angle = msg->angle_min + max_index * msg->angle_increment;

        // Store the angle
        direction_ = angle;
    }

    void controlLoop() {
        // Publish velocity commands based on direction
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = 0.1; // Fixed linear velocity
        msg.angular.z = direction_ / 2; // Adjust angular velocity based on direction
        velocity_publisher_->publish(msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_subscriber_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    float direction_ = 0.0;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Patrol>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
