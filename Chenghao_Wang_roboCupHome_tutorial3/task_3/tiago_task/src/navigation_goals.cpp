#include <tiago_task/navigationClass.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


navigationSpace::navigationClass::navigationClass()
{
    //INITIALIZE MEMBER VARIABLES
    count_mutex = PTHREAD_MUTEX_INITIALIZER;
    loc_acc = 1.0;
}

navigationSpace::navigationClass::~navigationClass()
{

}

void navigationSpace::navigationClass::getLocCov(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg)
{
    pthread_mutex_lock( &this->count_mutex );
    //COPY THE MSG TO A LOCAL VARIABLE
    this->loc_acc=msg->pose.covariance[0]+msg->pose.covariance[7];
    pthread_mutex_unlock( &this->count_mutex );
}

void navigationSpace::navigationClass::arm_move(moveit::planning_interface::MoveGroupInterface& group_arm_torso, double *pos)
{
  //set parameter
  std::map<std::string, double> target_position;
  target_position["torso_lift_joint"] = pos[0];
  target_position["arm_1_joint"] = pos[1];
  target_position["arm_2_joint"] = pos[2];
  target_position["arm_3_joint"] = pos[3];
  target_position["arm_4_joint"] = pos[4];
  target_position["arm_5_joint"] = pos[5];
  target_position["arm_6_joint"] = pos[6];
  target_position["arm_7_joint"] = pos[7];

  //choose planer
  ROS_INFO("Choose planner");
  group_arm_torso.setPlannerId("SBLkConfigDefault");

  //set target
  std::vector<std::string> torso_arm_joint_names;
  torso_arm_joint_names = group_arm_torso.getJoints();

  group_arm_torso.setStartStateToCurrentState();
  group_arm_torso.setMaxVelocityScalingFactor(1.0);

  for (unsigned int i = 0; i < torso_arm_joint_names.size(); ++i)
  {
    if ( target_position.count(torso_arm_joint_names[i]) > 0 )
    {
      ROS_INFO_STREAM("\t" << torso_arm_joint_names[i] << " goal position: " << target_position[torso_arm_joint_names[i]]);
      group_arm_torso.setJointValueTarget(torso_arm_joint_names[i], target_position[torso_arm_joint_names[i]]);
    }
  }

  //set plan
  ROS_INFO("Set plan");
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  //set maximum time to find a plan
  group_arm_torso.setPlanningTime(5.0);
  bool success = group_arm_torso.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS;

  if ( !success )
  {
    ROS_INFO("No plan found");
    return;
  }

  ROS_INFO("Move start");
  group_arm_torso.move();
  ROS_INFO("Move end");
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "navigation_goals");
  ros::NodeHandle n;
  ros::Duration(15).sleep();
  ros::Rate r(60);

  //prepare for localization
  navigationSpace::navigationClass navigationF;

  ros::Subscriber loc_sub = n.subscribe("/amcl_pose",100,
                                      &navigationSpace::navigationClass::getLocCov,
                                      &navigationF);

  ros::Publisher key_pub=n.advertise<geometry_msgs::Twist>("/key_vel",100);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  geometry_msgs::Twist msg;
  move_base_msgs::MoveBaseGoal goal;
  std_srvs::Empty srv;

  //start localization
  ROS_INFO("Localization start");
  ros::service::call("/global_localization", srv);

  //set rotation
  msg.angular.z = 1;

  //rotate until localization is done
  while(navigationF.loc_acc>0.018)
  {
    key_pub.publish(msg);
    ros::spinOnce();
    r.sleep();
  }

  ros::service::call("/move_base/clear_costmaps", srv);
  ROS_INFO("Localization end");

  //start flip
  ROS_INFO("Flip start");
  double arm_pos[8] = {0.0,1.26,-0.61,-2.08,0.69,-0.51,1.0,-0.34};

  ros::AsyncSpinner spinner(2);
  spinner.start();

  //std::vector<std::string> torso_arm_joint_names;
  moveit::planning_interface::MoveGroupInterface group_arm_torso("arm_torso");

  //move to the table
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = -1.0;
  goal.target_pose.pose.position.y = -12.4;
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.707;
  goal.target_pose.pose.orientation.w = 0.707;
  ac.sendGoal(goal);
  ac.waitForResult();

  //flip the table
  ROS_INFO("Arm Move start");
  navigationF.arm_move(group_arm_torso, arm_pos);
  arm_pos[2] = 1.07;
  arm_pos[6] = -0.8;
  navigationF.arm_move(group_arm_torso, arm_pos);
  arm_pos[0] = 0.14;
  arm_pos[1] = 0.2;
  arm_pos[2] = -1.34;
  arm_pos[3] = -0.2;
  arm_pos[4] = 1.94;
  arm_pos[5] = -1.57;
  arm_pos[6] = 1.37;
  arm_pos[7] = 0.0;
  navigationF.arm_move(group_arm_torso, arm_pos);
  spinner.stop();
  ROS_INFO("Arm Move end");
  ROS_INFO("Flip end");

  //start move
  ros::Duration(5).sleep();
  ROS_INFO("Navigation start");
  goal.target_pose.header.frame_id = "map";

  while(ros::ok())
  {
    //move to A
    ROS_INFO("Move to A");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -3.0;
    goal.target_pose.pose.position.y = -2.35;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.91;
    goal.target_pose.pose.orientation.w = 0.43;
    ac.sendGoal(goal);
    ac.waitForResult();

    //move to B
    ROS_INFO("Move to B");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -3.8;
    goal.target_pose.pose.position.y = -6.5;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 1.0;
    goal.target_pose.pose.orientation.w = 0.0;
    ac.sendGoal(goal);
    ac.waitForResult();

    //move to C
    ROS_INFO("Move to C");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -1.5;
    goal.target_pose.pose.position.y = -12.0;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.0;
    ac.sendGoal(goal);
    ac.waitForResult();
  }

  return 0;
}
