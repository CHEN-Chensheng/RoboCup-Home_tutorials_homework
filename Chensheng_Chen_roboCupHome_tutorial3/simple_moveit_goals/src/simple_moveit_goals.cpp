#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_srvs/Empty.h" 

#include <play_motion_msgs/PlayMotionAction.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <string>
#include <vector>
#include <map>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_moveit_goals");
  
  MoveBaseClient ac("move_base", true);
  ros::NodeHandle n;

  actionlib::SimpleActionClient<play_motion_msgs::PlayMotionAction> client("/play_motion", true);
  ros::ServiceClient global_localization = n.serviceClient<std_srvs::Empty>("global_localization");
  std_srvs::Empty srv;   // 用service来调用全局定位
  if (!global_localization.call(srv))
  {
     ROS_ERROR("Failed to call service global_localization");
  }
 

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.pose.position.x = 0.4248;
  goal.target_pose.pose.position.x = 0.0111;
  //goal.target_pose.pose.orientation.z = 0.7066;
  goal.target_pose.pose.orientation.w = 1.0;
  ac.sendGoal(goal);
  ROS_INFO("Sending goal 1");
  ac.waitForResult();
  

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -3.5315;
     goal.target_pose.pose.position.y = -0.0831;
     goal.target_pose.pose.orientation.z = -0.6937;
     goal.target_pose.pose.orientation.w = 0.7203;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 2");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -3.9237;
     goal.target_pose.pose.position.y = -2.4688;
     //goal.target_pose.pose.orientation.z = -0.7077;
     goal.target_pose.pose.orientation.w = 0.1;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 3");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -2.8839;
     goal.target_pose.pose.position.y = -2.3567;
     goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 4");
     ac.waitForResult();
     ros::Duration(2.0);


     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -4.0104;
     goal.target_pose.pose.position.y = -2.4399;
     goal.target_pose.pose.orientation.z = 0.7067;
     goal.target_pose.pose.orientation.w = 0.7075;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 5");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -4.0371;
     goal.target_pose.pose.position.y = -0.0221;
     goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 6");
     ac.waitForResult();
     //ros::Duration(2.0);
    
     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = 1.3405;
     goal.target_pose.pose.position.y = -0.3097;
     goal.target_pose.pose.orientation.z = -0.7388;
     goal.target_pose.pose.orientation.w = 0.6739;
     ROS_INFO("Sending goal 7");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = 1.2213;
     goal.target_pose.pose.position.y = -5.7613;
     goal.target_pose.pose.orientation.z = 1.0;
     //goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 8");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -3.9844;
     goal.target_pose.pose.position.y = -6.4977;
     goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 9");
     ac.waitForResult();
     ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -4.5783;
     goal.target_pose.pose.position.y = -6.6565;
     goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 10");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -4.4382;
     goal.target_pose.pose.position.y = -12.0971;
     //goal.target_pose.pose.orientation.z = 0.6710;
     goal.target_pose.pose.orientation.w = 1.0;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 11");
     ac.waitForResult();
     //ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = -1.44;
     goal.target_pose.pose.position.y = -11.7751;
     goal.target_pose.pose.orientation.z = 0.7068;
     goal.target_pose.pose.orientation.w = 0.7074;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 12");
     ac.waitForResult();
     ros::Duration(2.0);

     
     geometry_msgs::PoseStamped goal_pose;
     goal_pose.header.frame_id = "base_footprint";
     goal_pose.pose.position.x = 0.4;
     goal_pose.pose.position.y = 0.7;
     goal_pose.pose.position.z = 1.1;
     goal_pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0.0, 0.0, 0.0);
   
     ros::NodeHandle nh;
     ros::AsyncSpinner spinner(1);
     spinner.start();
   
     std::vector<std::string> torso_arm_joint_names;
     //select group of joints
     moveit::planning_interface::MoveGroupInterface group_arm_torso("arm_torso");
     //choose your preferred planner
     group_arm_torso.setPlannerId("SBLkConfigDefault");
     group_arm_torso.setPoseReferenceFrame("base_footprint");
     group_arm_torso.setPoseTarget(goal_pose);
  
     ROS_INFO_STREAM("Planning to move " <<
                     group_arm_torso.getEndEffectorLink() << " to a target pose expressed in " <<
                     group_arm_torso.getPlanningFrame());
   
     group_arm_torso.setStartStateToCurrentState();
     group_arm_torso.setMaxVelocityScalingFactor(1.0);
   
   
     moveit::planning_interface::MoveGroupInterface::Plan my_plan;
     //set maximum time to find a plan
     group_arm_torso.setPlanningTime(5.0);
     bool success;
     success = (bool)group_arm_torso.plan(my_plan);
    
     if ( !success )
       throw std::runtime_error("No plan found");
     
   
     ROS_INFO_STREAM("Plan found in " << my_plan.planning_time_ << " seconds");
     
    // ros::spinOnce();
     // Execute the plan
     ros::Time start = ros::Time::now();

      group_arm_torso.move();
   
     ROS_INFO_STREAM("Motion duration: " << (ros::Time::now() - start).toSec());




  ROS_INFO("Waiting for Action Server ...");
  client.waitForServer();

  play_motion_msgs::PlayMotionGoal goal_status;

  goal_status.motion_name = "home";
  goal_status.skip_planning = false;
  goal_status.priority = 0;

  ROS_INFO_STREAM("Sending goal with motion: " << "home");
  client.sendGoal(goal_status);

  ROS_INFO("Waiting for result ...");
  bool actionOk = client.waitForResult(ros::Duration(30.0));

  actionlib::SimpleClientGoalState state = client.getState();

  if ( actionOk )
  {
      ROS_INFO_STREAM("Action finished successfully with state: " << state.toString());
  }
  else
  {
      ROS_ERROR_STREAM("Action failed with state: " << state.toString());
  }





   
    
   
     spinner.stop();

  

 

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
  
  return 0;
}
