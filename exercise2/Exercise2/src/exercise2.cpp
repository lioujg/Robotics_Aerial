#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <Eigen/Geometry>
#include <eigen3/Eigen/Dense>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ncrl_tf_learning");
  ros::NodeHandle nh;
  //marker_pub publish "visualization_msgs::Marker" of message form
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  ros::Rate r(30);

  while (ros::ok())
  {
    //vector
    Eigen::Vector3d point(1.0 , 0.0 ,1.0);

    //rotation 90 度
    Eigen::Quaterniond rotation(std::sqrt(2)/2 , 0, std::sqrt(2) /2 , 0);

    //after rotation vector
    Eigen::Vector3d after_point;

    //No after_point = point * rotation * point^(-1);
    //Eigen will autonomously cahge form which rotation * point as point * rotation * point^(-1);
    after_point = rotation * point;

    std::cout<<"Answer is : \n"<<after_point<<std::endl;

    //rviz show the vector
    visualization_msgs::Marker Origin_point , Origin_after_point;
    //WORLD is Rviz coordinate
    Origin_point.header.frame_id = Origin_after_point.header.frame_id = "WORLD";
    Origin_point.header.stamp = Origin_after_point.header.stamp = ros::Time::now();

    //ns is namespace
    Origin_point.ns = "Origin_point";
    Origin_point.action = visualization_msgs::Marker::ADD;
    Origin_point.type = visualization_msgs::Marker::ARROW;

    Origin_after_point.ns = "Origin_after_point";
    Origin_after_point.action = visualization_msgs::Marker::ADD;
    Origin_after_point.type = visualization_msgs::Marker::ARROW;

    //Scale of ARROW
    Origin_point.scale.x = 0.08;
    Origin_point.scale.y = 0.08;

    //color of ARROW
    Origin_point.color.g = 1.0f;
    Origin_point.color.a = 1.0;

    Origin_after_point.scale.x = 0.08;
    Origin_after_point.scale.y = 0.08;

    Origin_after_point.color.r = 1.0f;
    Origin_after_point.color.a = 1.0;

    //geometry_msgs is anthor ROS message form which be used to push_back into visualization_msgs::Marker
    geometry_msgs::Point p ,p1 ,origin;
    origin.x =0.0;
    origin.y =0.0;
    origin.z =0.0;

    p.x = point.x();
    p.y = point.y();
    p.z = point.z();

    p1.x = after_point.x();
    p1.y = after_point.y();
    p1.z = after_point.z();


    Origin_point.points.push_back(origin);
    Origin_point.points.push_back(p);

    Origin_after_point.points.push_back(origin);
    Origin_after_point.points.push_back(p1);

    marker_pub.publish(Origin_point);
    marker_pub.publish(Origin_after_point);

    //set transformation
    static tf::TransformBroadcaster br;

    //br.sendTransform(tf::StampedTransform(tf::Transform,ros::Time::now(),"frame1","frame2"));
    //tf::Transform(tf::Quaternion ,tf::Vector3)


    br.sendTransform(
          tf::StampedTransform(
          tf::Transform
          (
          tf::Quaternion(0, 0, 0, 1), //rotate O to WORLD
          tf::Vector3(0.0, 0.0, 0.0) //translate O to WORLD
          ),
          ros::Time::now()
          ,"WORLD"                  //parents frame
          ,"O")                     //children frame
          );

    r.sleep();
  }

  return 0;
}

