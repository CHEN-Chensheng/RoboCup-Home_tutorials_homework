#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Char.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/transform_listener.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


// PCL specific includes
#include <pcl_ros/point_cloud.h> // enable pcl publishing
#include <sensor_msgs/PointCloud2.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>

//#include <image_geometry/pinhole_camera_model.h>


#include <perception_msgs/Rect.h>
#include <darknet_ros_msgs/BoundingBoxes.h>

#include <string.h>


using namespace std;
using namespace cv;

class calculate
{
private:
  int xmin, xmax, ymin, ymax;
  int i = 0;
  string class1;
  ros::NodeHandle nh_;
  //! Node handle in the private namespace
  ros::NodeHandle priv_nh_;

  ros::Subscriber sub;
  ros::Publisher pub1;

  perception_msgs::Rect Rect;

  void processCloud(const darknet_ros_msgs::BoundingBoxesConstPtr& pc);


public:
  calculate(ros::NodeHandle nh): nh_(nh), priv_nh_("~")
  {

    ROS_INFO_STREAM("Give me the desired class1");
    cin >> class1;

    sub = nh_.subscribe<darknet_ros_msgs::BoundingBoxes>("/darknet_ros/bounding_boxes", 100, &calculate::processCloud, this);

    ROS_INFO("object_recognition initialized ...");

    pub1 = nh_.advertise<perception_msgs::Rect>("Output_Rect", 1);
    //pub1.publish(Rect);
  }
  ~calculate() {}
};

void calculate::processCloud(const darknet_ros_msgs::BoundingBoxesConstPtr& pc)
{


  //cin >> class1;

  for(i = 0; i < pc->bounding_boxes.size(); i++)
  {
    if(pc->bounding_boxes[i].Class == "bottle" && pc->bounding_boxes[i].Class == class1 && pc->bounding_boxes[i].probability > 0.7)
    {
      xmin = pc->bounding_boxes[i].xmin;
      ymin = pc->bounding_boxes[i].ymin;
      xmax = pc->bounding_boxes[i].xmax;
      ymax = pc->bounding_boxes[i].ymax;
      Rect.x = xmin;
      Rect.y = ymax;
      Rect.width = xmax - xmin;
      Rect.height = ymax - ymin;
    }
    if(pc->bounding_boxes[i].Class == "cup" && pc->bounding_boxes[i].Class == class1)
    {
      xmin = pc->bounding_boxes[i].xmin;
      ymin = pc->bounding_boxes[i].ymin;
      xmax = pc->bounding_boxes[i].xmax;
      ymax = pc->bounding_boxes[i].ymax;
      Rect.x = xmin;
      Rect.y = ymax;
      Rect.width = xmax - xmin;
      Rect.height = ymax - ymin;
    }
    pub1.publish(Rect);



  }
}



int main(int argc, char** argv)
{

  ros::init(argc, argv, "object_recognition");
  ros::NodeHandle nh;

  calculate node(nh);

  ros::spin();
  return 0;
}
