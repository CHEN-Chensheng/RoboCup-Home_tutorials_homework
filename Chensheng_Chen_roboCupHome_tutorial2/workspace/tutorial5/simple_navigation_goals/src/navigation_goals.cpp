#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_srvs/Empty.h" 

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  
  MoveBaseClient ac("move_base", true);
  ros::NodeHandle n;
  ros::ServiceClient global_localization = n.serviceClient<std_srvs::Empty>("global_localization");
  std_srvs::Empty srv;
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

  //goal.target_pose.header.frame_id = "base_link";
  //goal.target_pose.pose.position.x = 1.0;
  //goal.target_pose.pose.orientation.w = 1.0;
  //ac.sendGoal(goal);
  //ROS_INFO("Sending goal 1+");
  //ac.waitForResult();
  

  while(ros::ok()){

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
     goal.target_pose.pose.position.x = -1.8349;
     goal.target_pose.pose.position.y = -12.1280;
     goal.target_pose.pose.orientation.z = 0.7012;
     goal.target_pose.pose.orientation.w = 0.7130;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 12");
     ac.waitForResult();
     ros::Duration(2.0);

     goal.target_pose.header.frame_id = "map";
     goal.target_pose.pose.position.x = 0.7006;
     goal.target_pose.pose.position.y = -12.0033;
     goal.target_pose.pose.orientation.z = 0.7071;
     goal.target_pose.pose.orientation.w = 0.7071;
     ac.sendGoal(goal);
     ROS_INFO("Sending goal 13");
     ac.waitForResult();
     ros::Duration(2.0);

  }

  

 

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
  
  return 0;
}
