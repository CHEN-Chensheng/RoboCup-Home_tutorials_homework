#include <iostream>
#include <fstream>
#include <ros/ros.h>
#include <simple_navigation_goals/myClass/simple_navigation_goalsClass.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

 int main(int argc, char** argv){
   ros::init(argc, argv, "simple_navigation");  //node's name

   ros::NodeHandle n;


    simple_navigation_goalsSpace::simple_navigation_goalsClass simple_navigationF(n);
    //simple_navigation_goalsSpace::simple_navigation_goalsClass navigationF(n);
    //ros::AsyncSpinner spinner(2);
    //spinner.start();

     ros::Subscriber loc_sub = n.subscribe("/amcl_pose",100,
                                         &simple_navigation_goalsSpace::simple_navigation_goalsClass::getLocCov,
                                         &simple_navigationF);





       ros::ServiceServer service1 = n.advertiseService("/navigation/action",/*service建立，在ROS中发布*/
                                                   &simple_navigation_goalsSpace::simple_navigation_goalsClass::communion1,
                                                   &simple_navigationF);

   ros::spin();
   //spinner.waitForShutdown();
   //ros::waitForShutdown();

   return 0;
 }

