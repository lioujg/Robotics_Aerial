/*
  Author : Ben You
  Target : control your turtlesim to goal_point
  Date : 03/16 2020
*/

// include ros library
#include "ros/ros.h"
// include msg library
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
// include math 
#include <math.h>

using namespace std;

turtlesim::Pose pose;
geometry_msgs::Twist vel_msg;
geometry_msgs::Point goal_point;
ros::Publisher turtlesim_pub;
bool reset;
struct XYZ{
    	float x;
	float y;
	float z;
};
struct XYZ pos_err_I;
// declare call back function
void pos_cb(const turtlesim::Pose::ConstPtr& msg)
{
	pose = *msg;
}
void rotate2D(float &x, float &y, float theta)
{
	float x1 = x;
	float y1 = y;
	x = cos(theta) * x1 - sin(theta) * y1;
	y = sin(theta) * x1 + cos(theta) * y1;
} 
void Pcontrol(const geometry_msgs::Point &desired) {
	ROS_INFO("Start control");
	// error in inertia frame
	pos_err_I.x = desired.x - pose.x;
	pos_err_I.y = desired.y - pose.y;
	float error_norm = sqrt(pow(pos_err_I.x, 2) + pow(pos_err_I.y, 2));
	// Find the goal_point position in Body(turtlesim) frame
	rotate2D(pos_err_I.x, pos_err_I.y, -pose.theta);
	// Find the error theta by  the goal_point position in Body frame
	float error_theta = atan2(pos_err_I.y,pos_err_I.x);
	//limit the linear control input
	if (error_norm >= 1) error_norm = 1;
	//Publish control input	
	vel_msg.linear.x = error_norm;
	vel_msg.angular.z = error_theta;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "tutorial_1");
  	ros::NodeHandle n;
  	// declare publisher & subscriber
  	ros::Subscriber pos_sub = n.subscribe<turtlesim::Pose>("turtle1/pose", 1, pos_cb);
  	turtlesim_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
	//input your desired position
	ROS_INFO("Please input (x,y). x>0,y>0");
	cout<<"desired_X:";
	cin>>goal_point.x;
	cout<<"desired_Y:";
	cin>>goal_point.y;
	// setting frequency as 10 Hz
  	ros::Rate loop_rate(10);
  	int count = 0;
  	while (ros::ok()){
    		//ROS_INFO("\ncount : %d\n",count);
    		ROS_INFO("goal x : %f \t y : %f\n",goal_point.x,goal_point.y);
    		ROS_INFO("pose x : %f \t y : %f\n",pose.x,pose.y);
    		ROS_INFO("pose theta: %f \n",pose.theta);
		//Input your goal_point to your controller
    		Pcontrol(goal_point);
		//Input your control input(from Pcontrol) to your plant
    		turtlesim_pub.publish(vel_msg);
    		count ++;
    		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
