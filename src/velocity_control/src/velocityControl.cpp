/*
功能：接受速度控制指令，转化为PWM信号，发布出去
订阅：enconder话题  100hz
     joy话题
     cmd_vel话题  Twist类型
发布：PWM话题
*/
#include <ros/ros.h>
#include <std_msgs/UInt8MultiArray.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <sstream>
#include <iostream>
using namespace std;

double velocity_left;
double velocity_right;


void enconderCallback(const std_msgs::Int16MultiArray::ConstPtr& enconder)
{
  //enconder_left = enconder->data[1];
  //enconder_right = enconder->data[2];
  velocity_left = (enconder->data[1])*0.87222;
  //velocity_left =enconder_left*0.87222;
  velocity_right = (enconder->data[1])*0.87222;
  ROS_INFO("velocity_left=%f,velocity_right=%f",velocity_left,velocity_right);
}
void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel)
{
  
  
}
int main(int argc,char **argv)
{
  ros::init(argc,argv,"velocityControl");
  ros::NodeHandle n;
  ros::Publisher velocity_pub =
        n.advertise<std_msgs::UInt8MultiArray>("PWM",1000);
  ros::Subscriber enconder_sub =n.subscribe("enconder",1000,enconderCallback);
  ros::Subscriber cmdVel_sub = n.subscribe("cmd_vel",1000,cmdVelCallback);
  std_msgs::UInt8MultiArray arduino_pwm;
  arduino_pwm.data.resize(2);
  arduino_pwm.data[1]=5;
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
    //ROS_INFO("haha哈" );
    //printf("%d哈哈\n",arduino_pwm.data.back());
    
    velocity_pub.publish(arduino_pwm);
    ros::spinOnce();
    loop_rate.sleep();
    
  }

}