cmake_minimum_required(VERSION 2.8.3)
project(Exercise2)

set(CMAKE_BUILD_TYPE "Debug")

#set C++ version
set(CMAKE_CXX_FLAGS "-std=c++11")


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  tf
  visualization_msgs
)

find_package(Eigen3 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES Exercise2
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
DEPENDS EIGEN3
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)


add_executable(exercise2 src/exercise2.cpp)
target_link_libraries(exercise2 ${catkin_LIBRARIES} )
