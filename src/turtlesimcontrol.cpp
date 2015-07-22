#include "ros/ros.h"
#include "geometry_msgs/Twist.h" // turtle's cmd_vel
#include "turtlesim/Pose.h" // reading turtle's position


void turtleCallback(const turtlesim::Pose::ConstPtr& msg);


int main(int argc, char** argv)
{
  // Initialized the node, setup the NodeHandle
  // for handling the communication with the ROS system
  ros::init(argc, argv, "turtlesimcontrol_node");
  ros::NodeHandle nh;// Define the subscriber to turtle's position
  ros::Subscriber sub = nh.subscribe("turtle1/pose", 1, turtleCallback);
  ros::Publisher pub;
  pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
  
  geometry_msgs::Twist turtle_cmd_vel;

  turtle_cmd_vel.linear.x = 1;
  pub.publish(turtle_cmd_vel);
  if(!pub)
  {
    ROS_ERROR("Message didn't send out");
  }
  // ros::spinOnce();
  // pub.publish(turtle_cmd_vel);
  

  ros::Rate rate(1);
  while(ros::ok() && nh.ok())
  {
    ros::spinOnce();
    pub.publish(turtle_cmd_vel);
  }

  return 0;
}

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
  ROS_INFO("Turtle lawnmower@[%f, %f, %f]", msg->x, msg->y, msg->theta);
}

