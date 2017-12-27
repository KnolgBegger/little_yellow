#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/UInt16MultiArray.h>

class TrackByLaser
{
public:
  TrackByLaser();
private:
  void laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laserDate);
  
  ros::NodeHandle nh_;
  
  ros::Publisher action_pub_;
  ros::Subscriber laser_sub_;
  
};

TrackByLaser::TrackByLaser()
{
  action_pub_ = nh_.advertise<std_msgs::UInt16MultiArray>("cmd_vel_laser",1);
  laser_sub_ =nh_.subscribe<sensor_msgs::LaserScan>("scan",10,&TrackByLaser::laserCallBack,this);
  
  
}
void TrackByLaser::laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laserdate)
{
  sensor_msgs::LaserScan date;
  std_msgs::UInt16MultiArray action_value;
  
  
  
  
  action_pub_.publish(action_value);
  
}


int main(int argc , char** argv)
{
  ros::init(argc,argv,"trackByLaser");
  
  ros::spin();
  
}