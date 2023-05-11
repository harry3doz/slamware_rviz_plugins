#pragma once

#ifndef Q_MOC_RUN  
  #include <QObject>

  #include <ros/ros.h>

  #include <rviz/default_plugin/tools/pose_tool.h>
#endif

namespace slamware_rviz_plugins
{
class SetPoseTool : public rviz::PoseTool
{
Q_OBJECT
public:
  // constructor
  SetPoseTool();
  // destructor
  ~SetPoseTool() override
  {
  }
  // init function
  void onInitialize() override;

protected:
  void onPoseSet(double x, double y, double theta) override;

private Q_SLOTS:
  void updateTopic();

private:
  ros::NodeHandle nh_;
  ros::Publisher pub_;
  char shortcut_key_;
  std::string topic_name_;  // publish topic

};

}  // end namespace slamware_rviz_plugins

