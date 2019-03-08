#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
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
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

#include <image_geometry/pinhole_camera_model.h>


// Visualization
//#include <visualization_msgs/MarkerArray.h>
//#include <visualization_msgs/Marker.h>





//#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <geometry_msgs/PoseStamped.h>

using namespace std;
using namespace cv;


//! Plane segmentation class
//! computes and split the big planes from the rest of the point cloud clusters
class PlaneSegmentation
{

private:
    //! The node handle
    ros::NodeHandle nh_;
    //! Node handle in the private namespace
    ros::NodeHandle priv_nh_;


    //! Subscribers to the PointCloud data
    // Optional: MESSAGE FILTERS COULD BE A GOOD IDEA FOR GRABBING MULTIPLE TOPICS SYNCRONIZED, NOT NEEDED THOUGH


    //! Publisher for pointclouds
    ros::Publisher pub_plane_pc_;
    ros::Publisher pub_clusters_pc_;


    //! Parameters



    //! Internal data
    pcl::PointCloud<pcl::PointXYZ> curr_table_pc;
    pcl::PointCloud<pcl::PointXYZ> curr_clusters_pc;


    //------------------ Callbacks -------------------

    //! Callback for service calls
	

    //! Callback for subscribers
    //! Complete processing of new point cloud
    void processCloud(const sensor_msgs::TypeConstPtr &var); // for multiple data topics (const sensor_msgs::TypeConstPtr &var, const sensor_msgs::TypeConstPtr &var, ...)

public:
    //! Subscribes to and advertises topics
    PlaneSegmentation(ros::NodeHandle nh) : nh_(nh), priv_nh_("~") //,
        //sub(nh, "topic", 5) // constructor initialization form for the subscriber if needed
    {


        pub_plane_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/plane_points", 10);
        pub_clusters_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/clusters_points", 10);



        // Callback function register

        //initialize params



    }

    ~PlaneSegmentation() {}
};

//! Callback for processing the Point Cloud data
void PlaneSegmentation::processCloud(const sensor_msgs::TypeConstPtr &var)
{

    pcl::PointCloud< pcl::PointXYZ > pc; // internal data
    

   
	// Convert the data to the internal var (pc) using pcl function: fromROSMsg
	// TODO


    

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = pc.makeShared(); // cloud to operate
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f( new pcl::PointCloud<pcl::PointXYZ> ); // cloud to store the filter the data

    std::cout << "PointCloud before filtering has: " << pc.points.size() << " data points." << std::endl; //*
    std::cout << "width: " << pc.width << "height: " << pc.height << std::endl;


    // Down sample the pointcloud using VoxelGrid
	// TODO

    //----

    std::cout << "PointCloud after filtering has: " << cloud_filtered->points.size()  << " data points." << std::endl;
    


    // Create the segmentation object for the plane model and set all the parameters using pcl::SACSegmentation<pcl::PointXYZ>
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers( new pcl::PointIndices );
    pcl::ModelCoefficients::Ptr coefficients( new pcl::ModelCoefficients );
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane( new pcl::PointCloud<pcl::PointXYZ>() );

    // set parameters of the SACS segmentation
	// TODO

    //----

    int nr_points = (int) cloud_filtered->points.size();

    // Segment the planes using pcl::SACSegmentation::segment() function and pcl::ExtractIndices::filter() function
	// TODO
        // If you want to extract more than one plane you have to do a while


    //----


    // Publish biggest plane
	// TODO
	// Tips: 
	// - you can copy the pointcloud using cl::copyPointCloud()
	// - Set the header frame_id to the pc2 header frame_id
	// - you can use pcl_conversions::toPCL() to convert the stamp from pc2 header to pointcloud header stamp
	// - to publish -> pub_plane_pc_.publish( pointcloud_variable.makeShared() )
    //----


    // Publish other clusters
    // TODO similar to the previous publish
    


    return;


}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "plane_segmentation");
    ros::NodeHandle nh;
    PlaneSegmentation node(nh);
    ros::spin();
    return 0;
}


