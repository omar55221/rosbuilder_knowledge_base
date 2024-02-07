cmake_minimum_required(VERSION 3.0.2)
project(robot_gui)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  robotinfo_msgs
  roscpp
  std_srvs
)

# Find OpenCV
find_package(OpenCV REQUIRED)

catkin_package()

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS} 
  /home/user/catkin_ws/src/robot_gui/src
)

add_executable(robot_gui_node src/robot_gui_node.cpp)
target_link_libraries(robot_gui_node ${catkin_LIBRARIES})
target_link_libraries(robot_gui_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}  # Link OpenCV libraries
)
target_link_libraries(robot_gui_node cvui)
