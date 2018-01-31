/*
功能：接受速度控制指令，转化为PWM信号，发布出去
订阅：enconder话题
     joy话题
     cmd_vel话题
发布：PWM话题
*/
#include <ros/ros.h>
#include <std_msgs/UInt8MultiArray.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Int16MultiArray.h>
#include <sstream>
#include <iostream>
using namespace std;



void enconderCallback(const std_msgs::Int16MultiArray::ConstPtr& enconder)
{
  ROS_INFO("enconder_left=%d,enconder_right=%d",enconder->data[1],enconder->data[2]);
  
  
}
int main(int argc,char **argv)
{
  ros::init(argc,argv,"velocityControl");
  ros::NodeHandle n;
  ros::Publisher velocity_pub =
        n.advertise<std_msgs::UInt8MultiArray>("PWM",1000);
  ros::Subscriber enconder_sub =n.subscribe("enconder",1000,enconderCallback);
  uint8_t a;
  a = 10;
  std_msgs::UInt8MultiArray arduino_pwm;
  arduino_pwm.data.resize(5);
  arduino_pwm.data.push_back(a);
  arduino_pwm.data.push_back(a);
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