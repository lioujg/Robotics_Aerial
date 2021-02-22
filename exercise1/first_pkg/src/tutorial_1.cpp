/*
  Author : Vivan
  Target : Let turtlesim go straight forward with speed 1 m/s
  Annotator : Chad Lin
  Date : 11/07 2018
*/

// include ros library
#include "ros/ros.h"

// include msg library
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>


geometry_msgs::Twist vel_msg;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tutorial_1");
  ros::NodeHandle n;
  // declare publisher & subscriber
  ros::Publisher turtlesim_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);

  // setting frequency as 10 Hz
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok()){

    vel_msg.linear.x= 0.5;
    vel_msg.linear.y= 0;
    vel_msg.linear.z= 0;

    vel_msg.angular.x= 0;
    vel_msg.angular.y= 0;
    vel_msg.angular.z= 0.2;

    turtlesim_pub.publish(vel_msg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}



