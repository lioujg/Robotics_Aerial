cmake_minimum_required(VERSION 2.8.3) 
project(first_pkg)
find_package(catkin REQUIRED COMPONENTS 
roscpp 
rospy 
std_msgs genmsg
)
catkin_package(
)
include_directories(include ${catkin_INCLUDE_DIRS})  
## build

add_executable(talker_2 src/talker_2.cpp)
target_link_libraries(talker_2 ${catkin_LIBRARIES})

add_executable(listener_2 src/listener_2.cpp) 
target_link_libraries(listener_2 ${catkin_LIBRARIES})

add_executable(tutorial_1 src/tutorial_1.cpp)
target_link_libraries(tutorial_1 ${catkin_LIBRARIES})
add_dependencies(tutorial_1 beginner_tutorials_generate_messages_cpp)
