/*
  Author : Ben You
  Target : Mechanical 2-order system simulation
  Date : 03/25 2020
*/
#include "ros/ros.h"
#include "std_msgs/Float64.h"
using namespace std;
/*The dynamic system can be represented as "M*y_doubledot + b*y_dot + k*y = u ";
* Control canonical form:
* [x1_dot] = [0       1][x1] + [0]u;
* [x2_dot] = [-k/M -b/M][x2] + [1/M]u;
* x1 = y;
* x2 = y_dot;
* y = [1 0][x1];
*          [x2];
*/
struct Dynamic_State {
	float last = 0;
	float current = 0;
};
int main(int argc, char **argv)
{
	ros::init(argc,argv,"dynamic");
	ros::NodeHandle nh;
	ros::Publisher state_pub = nh.advertise<std_msgs::Float64>("/Position",10);
	/*Parameters initialization*/
	float M = 2;//mass
	float k = 1;//spring constant
	float b = 0.707;//damping coefficient
	float u = 1;//control input is unit step function
	struct Dynamic_State x2;//velocity
	struct Dynamic_State x1;//position
	ros::Rate loop_rate(10);
	double past = ros::Time::now().toSec();
	double dt;//sampling time
	std_msgs::Float64 position;
	/*Compute the position*/
	while(ros::ok()) {
		double now = ros::Time::now().toSec();
		/*Discrete-Time Linear State-Space*/
		dt = now - past;
		x2.current = x2.last + dt*(-(k/M)*x1.last - (b/M)*x2.last + (1/M)*u);
		x1.current = x1.last + dt*x2.last;
		/*Current moment is last moment in the future*/
		x2.last = x2.current;
		x1.last = x1.current;
		past = now;
		//float y = x1.current;
		//ROS_INFO("Position:%f",y);
		/*You can check the position data by PlotJuggler or rqt_plot*/
		position.data = x1.current; 
		state_pub.publish(position);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

