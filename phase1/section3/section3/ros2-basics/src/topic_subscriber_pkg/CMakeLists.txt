cmake_minimum_required(VERSION 3.8)
project(topic_subscriber_pkg)

# Standard CMake lines
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)  # Needed for move_robot_node

# Add executables
add_executable(simple_subscriber_node src/simple_topic_subscriber.cpp)
add_executable(move_robot_node src/move_robot.cpp)  # Add this line

# Declare dependencies for each executable
ament_target_dependencies(simple_subscriber_node rclcpp std_msgs)
ament_target_dependencies(move_robot_node rclcpp geometry_msgs)  # Add this line

# Install targets
install(TARGETS 
  simple_subscriber_node 
  move_robot_node  # Add this line
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

# Linting
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
