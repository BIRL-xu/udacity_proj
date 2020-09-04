#ifndef PATH_TRACKER_H
#define PATH_TRACKER_H

#include <iterator>
#include <ros/ros.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <string>

#include "udacity_proj_pkg/LQR.h"


//gazebo
#include <gazebo_msgs/GetModelState.h>
/*
* @brief encapsulates ROS related stuff for path tracking
*/
class PathTrackerROS
{
public:
	PathTrackerROS();
	~PathTrackerROS();
	PathTrackerROS(ros::NodeHandle &node_);
	void PublishReferencePath();
	void PublishTrackedPath();
	void GetPath(std::string poses_file_name);

protected:
	nav_msgs::Path reference_path; 
	nav_msgs::Path tracked_path;
	nav_msgs::Path receding_horiz;
	geometry_msgs::Twist cmd_vel;
	geometry_msgs::PoseStamped GetCurrentPose(); 



private:
	ros::Publisher reference_path_pub;
	ros::Publisher tracked_path_pub;
	ros::Publisher receding_horiz_pub;
	ros::Publisher cmd_vel_pub; 
	//gazebo 
	gazebo_msgs::GetModelState robot_state;
	ros::ServiceClient robot_state_client;
	
};

/*
* @brief encapsulates the complete PathTracker object containing LQR(composition) and ROS related stuff(inheritance) 
*/
class PathTracker : public PathTrackerROS
{
public:
	PathTracker();
	PathTracker(std::string poses_file_name,  ros::NodeHandle &node_) ;
	~PathTracker();


private: 

	/* @brief LQR controller object 
	*/
	LQR _lqr; 

	/* @brief Initialize the tracker 
	*/
	void TrackerInit(); 

	/* @brief Runs the LQR algorithm
	*/
	void TrackPath(); 

	/* @brief Finds closest pose in the path to current pose and returns its index  
	*/
public:	int ClosestPose(); 
	
};






#endif