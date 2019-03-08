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



using namespace std;
using namespace cv;


class From2Dto3D
{

    private:
      //! The node handle
      ros::NodeHandle nh_;
      //! Node handle in the private namespace
      ros::NodeHandle priv_nh_;

      //! Define publishers and subscribers


      //! Define the pointcloud structure and the bounding box local copy


      //! A tf transform listener if needed
      tf::TransformListener listener_;


      //------------------ Callbacks -------------------

      //! Process clusters
      void processCloud(const sensor_msgs::PointCloud2ConstPtr& pc);
      //! Process bounding boxes
      void processRect(const perception_msgs::RectConstPtr & r);


    public:
      //! Subscribes to and advertises topics
      From2Dto3D(ros::NodeHandle nh) : nh_(nh), priv_nh_("~")
      {

        // subscribers to the bounding boxes and the point cloud
        // format:
        // sub_name = nh_.subscribe<Type>("topic", queuesize, Function_of_the_class, this);

        // Publishers
        // format:
        //pub_name = nh_.advertise< Type >("topic", queuesize);

        ROS_INFO("from2Dto3D initialized ...");

      }

      ~From2Dto3D() {}
};


void From2Dto3D::processCloud(const sensor_msgs::PointCloud2ConstPtr& pc)
{    
    // store local data copy or shared, depending on the message
}

void From2Dto3D::processRect(const perception_msgs::RectConstPtr& r)
{

    // process bounding box and send 3D position to the topic
    // tip: take a look at the pcl::PointXYZRGB structure
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "from2Dto3D");
    ros::NodeHandle nh;
    From2Dto3D node(nh);
    ros::spin();
    return 0;
}


