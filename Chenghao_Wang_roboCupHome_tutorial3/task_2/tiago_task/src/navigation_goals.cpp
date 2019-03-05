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

    ROS_INFO_STREAM("Get accuracy: "<<loc_acc);
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
  while(navigationF.loc_acc>0.015)
  {
    key_pub.publish(msg);
    ros::spinOnce();
    r.sleep();
  }

  ros::service::call("/move_base/clear_costmaps", srv);
  ROS_INFO("Localization end");

  //start move

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
