#ifndef SIMPLE_NAVIGAION_GOALSCLASS_H
#define SIMPLE_NAVIGAION_GOALSCLASS_H
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <simple_navigation_goals/SandR_1.h>
#include <simple_navigation_goals/SandR_2.h>

#include <std_srvs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>

using namespace Eigen;

namespace simple_navigation_goalsSpace
{
    class simple_navigation_goalsClass
    {
    public:

        simple_navigation_goalsClass(ros::NodeHandle nh);
        ~simple_navigation_goalsClass();

        geometry_msgs::Twist msg;
        std_srvs::Empty srv;

        ros::NodeHandle nh_;
        ros::NodeHandle priv_nh_;
        ros::ServiceClient local_client;
        ros::Publisher key_pub;


        bool communion1(simple_navigation_goals::SandR_1::Request &req, simple_navigation_goals::SandR_1::Response &res);
        double loc_acc;
        void getLocCov(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg);

    private:

        typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    };

}

#endif
