#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>

namespace navigationSpace
{
  class navigationClass
  {
  public:
    pthread_mutex_t count_mutex;
    double loc_acc;
    void getLocCov(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg);

    navigationClass();
    ~navigationClass();

  };
}
