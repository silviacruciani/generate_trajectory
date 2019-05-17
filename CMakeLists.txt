cmake_minimum_required(VERSION 2.8.3)
project(generate_trajectory)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  trajectory_msgs
  message_generation
  joint_trajectory_generator
)


## Generate services in the 'srv' folder
 add_service_files(
   FILES
   GenerateTrajectory.srv
)


## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   trajectory_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy trajectory_msgs
)

## Specify additional locations of header files
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


add_library(trajectory_generator src/${PROJECT_NAME}/trajectory_generator.cpp)

add_executable(trajectory_generator_server src/trajectory_generator_server.cpp)


target_link_libraries(trajectory_generator   ${catkin_LIBRARIES})
target_link_libraries(trajectory_generator_server   trajectory_generator ${catkin_LIBRARIES})