cmake_minimum_required(VERSION 3.0.2)
project(service_server_pkg)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  std_msgs
  message_generation
  roscpp
  std_srvs
)

## Declare ROS messages, services and actions
## No messages, services or actions are being used in this package

## Declare ROS dynamic reconfigure parameters
## No dynamic reconfigure parameters are being used in this package

## catkin specific configuration
catkin_package()

## Specify additional locations of header files
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(simple_service_server src/simple_service_server.cpp)

## Specify libraries to link the target against
target_link_libraries(simple_service_server ${catkin_LIBRARIES})

## Install the executable
install(TARGETS simple_service_server
         RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## No testing is being done in this package