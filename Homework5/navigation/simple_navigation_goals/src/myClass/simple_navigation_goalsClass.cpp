#include <ros/ros.h>
#include <simple_navigation_goals/myClass/simple_navigation_goalsClass.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_srvs/Empty.h>

namespace simple_navigation_goalsSpace
{
  simple_navigation_goalsClass::simple_navigation_goalsClass(ros::NodeHandle nh)
    : nh_(nh)/*, priv_nh_("~")  //主handle nh，派生出的nh_需要这样定义*/
//  simple_navigation_goalsClass::simple_navigation_goalsClass()
  {
      loc_acc = 100;
      local_client = nh_.serviceClient<std_srvs::Empty>("/global_localization");
    //ros::AsyncSpinner spinner(2); // Use 4 threads
    //spinner.start();

  }


  simple_navigation_goalsClass::~simple_navigation_goalsClass()
  {

  }


  bool simple_navigation_goalsClass::communion1(simple_navigation_goals::SandR_1::Request &req, simple_navigation_goals::SandR_1::Response &res)
  {

    MoveBaseClient ac("move_base", true);


    while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
    }

    if(req.s == 1)
    {
      ROS_INFO("Receive!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      //simple_navigation_goalsSpace::simple_navigation_goalsClass simple_navigationF_;
     // simple_navigation_goalsSpace::simple_navigation_goalsClass navigationF_;
      ros::NodeHandle n_;

      std_srvs::Empty srv;
      local_client.call(srv);
      ros::Rate r(60);
      key_pub=n_.advertise<geometry_msgs::Twist>("/key_vel",100); //use this topic to control robot to rotate

        //set rotation
        //local_client.msg.angular.z = 1;
        ROS_INFO("Integrate with each other!");
        loc_acc = 100;
        //rotate until localization is done
//      geometry_msgs::PoseWithCovarianceStamped::ConstPtr temp_msg =
//          ros::topic::waitForMessage<geometry_msgs::PoseWithCovarianceStamped>("/amcl_pose");
//      double temp_loc = temp_msg->pose.covariance[0]+temp_msg->pose.covariance[7];
//      temp_loc = 100;
        msg.angular.z = 1; // robot rotate
        while(loc_acc > 0.015)
        {
          key_pub.publish(msg);
          //ROS_INFO("Integrate with each other!!!!!!!!!!");
          ROS_INFO_STREAM("this->loc_acc="<<loc_acc);
          ros::spinOnce();
//          temp_msg = ros::topic::waitForMessage<geometry_msgs::PoseWithCovarianceStamped>("/amcl_pose");
//          temp_loc = temp_msg->pose.covariance[0]+temp_msg->pose.covariance[7];
          r.sleep();

        }
        loc_acc = 100;
        msg.angular.z = 0; //robot stops rotate
        key_pub.publish(msg);
        res.r = true;
      ROS_INFO("Localization Succeeded!");

      return true;
      //continue;
    }
    
    if(req.s == 2)
    {
      //ROS_INFO("Receive!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      move_base_msgs::MoveBaseGoal goal;

      goal.target_pose.header.frame_id = "map";
      goal.target_pose.pose.position.x = -0.82366;
      goal.target_pose.pose.position.y = -1.63328;
      goal.target_pose.pose.orientation.z = 0.05706;
      goal.target_pose.pose.orientation.w = 0.99837;
      ac.sendGoal(goal);
      ROS_INFO("Go to initial point!");
      ac.waitForResult();

      res.r = true;

      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved 1 meter forward");
      else
      ROS_INFO("The base failed to move forward 1 meter for some reason");

      ROS_INFO("sending back response1 Succeesd!");
      return true;
    }

    if(req.s == 3)
    {
      //ROS_INFO("Receive!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      move_base_msgs::MoveBaseGoal goal;

      goal.target_pose.header.frame_id = "map";
      goal.target_pose.pose.position.x = -0.57783;
      goal.target_pose.pose.position.y = 0.34114;
      goal.target_pose.pose.orientation.z = 0.00840;
      goal.target_pose.pose.orientation.w = 0.99996;
      ac.sendGoal(goal);
      ROS_INFO("Go to table1!");
      ac.waitForResult();

      res.r = true;

      return true;
    }

    if(req.s == 4)
    {
      move_base_msgs::MoveBaseGoal goal;

      goal.target_pose.header.frame_id = "map";
      goal.target_pose.pose.position.x = -2.03227;
      goal.target_pose.pose.position.y = -1.64649;
      goal.target_pose.pose.orientation.z = -0.99940;
      goal.target_pose.pose.orientation.w =  0.034758;
      ac.sendGoal(goal);
      ROS_INFO("Go to table2!");
      ac.waitForResult();
      res.r =  true;

      return true;
   }
  }

  void simple_navigation_goalsSpace::simple_navigation_goalsClass::getLocCov(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg)
  {

      this->loc_acc=msg->pose.covariance[0]+msg->pose.covariance[7];

      ROS_INFO_STREAM("Get accuracy: "<<loc_acc);
  }
//  bool simple_navigation_goalsClass::communion2(simple_navigation_goals::SandR_2::Request &req, simple_navigation_goals::SandR_2::Response &res)
//  {
//    MoveBaseClient ac("move_base", true);

//    while(!ac.waitForServer(ros::Duration(5.0))){
//      ROS_INFO("Waiting for the move_base action server to come up");
//    }

//    move_base_msgs::MoveBaseGoal goal;

//     goal.target_pose.header.frame_id = "map";
//     goal.target_pose.pose.position.x = -1.38405;
//     goal.target_pose.pose.position.y = 3.71929;
//     goal.target_pose.pose.orientation.z = 0.69945;
//     goal.target_pose.pose.orientation.w = 0.71468;
//     ac.sendGoal(goal);
//     ROS_INFO("Sending goal 4");
//     ac.waitForResult();
//     res.r =  true;

//     if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//     {
//        ROS_INFO("Hooray, the base moved 1 meter forward");
//     }
//    else
//      ROS_INFO("The base failed to move forward 1 meter for some reason");

//    ROS_INFO("sending back response:  reply = %d", req.s);
//    return true;
//  }
}
