#include <tf/transform_listener.h>

#include <geometry_msgs/Pose.h>

#include <rviz/tool_manager.h>
#include <rviz/display_context.h>

#include "setpose_tool.h"

namespace slamware_rviz_plugins
{

SetPoseTool::SetPoseTool()
  : nh_()
{
  shortcut_key_ = 's';
  topic_name_ = "/slamware_ros_sdk_server_node/set_pose";
}

void SetPoseTool::onInitialize()
{
  PoseTool::onInitialize();
  setName("slamware set pose");
  updateTopic();
}

void SetPoseTool::updateTopic()
{
  try
  {
    pub_ = nh_.advertise<geometry_msgs::Pose>(topic_name_, 1);
  }
  catch (const ros::Exception& e)
  {
    ROS_ERROR_STREAM_NAMED("[Slamware]SetPoseTool", e.what());
  }
}

void SetPoseTool::onPoseSet(double x, double y, double theta)
{
  geometry_msgs::Pose pose;
  pose.position.x = x;
  pose.position.y = y;

  tf::Quaternion quat;
  quat.setRPY(0.0, 0.0, theta);
  tf::quaternionTFToMsg(quat, pose.orientation);
  ROS_INFO("Setting Pose: %.3f %.3f %.3f", x, y, theta);
  pub_.publish(pose);
}

}  // end namespace slamware_rviz_plugins

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(slamware_rviz_plugins::SetPoseTool, rviz::Tool)
