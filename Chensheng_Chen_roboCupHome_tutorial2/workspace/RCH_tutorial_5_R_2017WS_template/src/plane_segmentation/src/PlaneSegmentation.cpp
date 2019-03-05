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
    //message_filters::Subscriber<sensor_msgs::PointCloud2> sub_(nh_, "/xtion/depth_registered/point", 1);
    //sub_.registerCallback(PlaneSegmentation::processCloud);
    //sub_ = nh_.subscribe<sensor_msgs::PointCloud2>("/xtion/depth_registered/points", 1, &PlaneSegmentation::processCloud, this);

    //! Publisher for pointclouds
    ros::Publisher pub_plane_pc_;
    ros::Publisher pub_clusters_pc_;


    //! Parameters
    ros::Subscriber sub_2;


    //! Internal data
    pcl::PointCloud<pcl::PointXYZ> curr_table_pc;
    pcl::PointCloud<pcl::PointXYZ> curr_clusters_pc;


    //------------------ Callbacks -------------------

    //! Callback for service calls
	

    //! Callback for subscribers
    //! Complete processing of new point cloud
    void processCloud(const sensor_msgs::PointCloud2ConstPtr &var); // for multiple data topics (const sensor_msgs::TypeConstPtr &var, const sensor_msgs::TypeConstPtr &var, ...)

public:
    //! Subscribes to and advertises topics
    PlaneSegmentation(ros::NodeHandle nh) : nh_(nh), priv_nh_("~") //,
        //sub(nh, "topic", 5) // constructor initialization form for the subscriber if needed
    {

        sub_2 = nh_.subscribe<sensor_msgs::PointCloud2>("/xtion/depth_registered/points", 1, &PlaneSegmentation::processCloud, this);
        pub_plane_pc_ = nh_.advertise< sensor_msgs::PointCloud2 >("/segmentation/plane_points", 10);
      //pub_plane_pc_ = nh_.advertise< sensor_msgs::PointCloud2 >("/segmentation/plane_points", 10);
        pub_clusters_pc_ = nh_.advertise< sensor_msgs::PointCloud2 >("/segmentation/clusters_points", 10);



        // Callback function register

        //initialize params



    }

    ~PlaneSegmentation() {}
};

//! Callback for processing the Point Cloud data
void PlaneSegmentation::processCloud(const sensor_msgs::PointCloud2ConstPtr &var)
{

    pcl::PointCloud< pcl::PointXYZ > pc; // internal data
    //pcl::PointCloud< pcl::PointClo>
    sensor_msgs::PointCloud2 Out;
    sensor_msgs::PointCloud2 Out1;
   
	// Convert the data to the internal var (pc) using pcl function: fromROSMsg
	// TODO
    pcl::fromROSMsg(*var, pc);


    

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = pc.makeShared(); // cloud to operate   zhinengzhizhen
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f( new pcl::PointCloud<pcl::PointXYZ> ); // cloud to store the filter the data

    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);



    // Down sample the pointcloud using VoxelGrid
	// TODO
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloud_f);
    //----

    std::cout << "PointCloud after filtering has: " << cloud_f->points.size()  << " data points." << std::endl;
    


    // Create the segmentation object for the plane model and set all the parameters using pcl::SACSegmentation<pcl::PointXYZ>
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers( new pcl::PointIndices() );
    pcl::ModelCoefficients::Ptr coefficients( new pcl::ModelCoefficients() );
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane( new pcl::PointCloud<pcl::PointXYZ>() );

    // set parameters of the SACS segmentation
	// TODO
     seg.setOptimizeCoefficients(true);
     seg.setModelType(pcl::SACMODEL_PLANE);
     seg.setMethodType(pcl::SAC_RANSAC);
     seg.setMaxIterations (1000);
     seg.setDistanceThreshold(0.01);
     seg.setInputCloud(cloud_f);
     seg.segment(*inliers, *coefficients); //why input is *inliers, output is model_coefficients???

     if (inliers->indices.size () == 0)
     {
       PCL_ERROR ("Could not estimate a planar model for the given dataset.");
       //return (-1);
     }
     std::cerr << "Model coefficients: " << coefficients->values[0] << " "
                                           << coefficients->values[1] << " "
                                           << coefficients->values[2] << " "
                                           << coefficients->values[3] << std::endl;

       std::cerr << "Model inliers: " << inliers->indices.size () << std::endl;
       for (size_t i = 0; i < inliers->indices.size (); ++i)
         std::cerr << inliers->indices[i] << "    " << cloud->points[inliers->indices[i]].x << " "
                                                    << cloud->points[inliers->indices[i]].y << " "
                                                    << cloud->points[inliers->indices[i]].z << std::endl;
    //----

    int nr_points = (int) cloud_f->points.size();

    // Segment the planes using pcl::SACSegmentation::segment() function and pcl::ExtractIndices::filter() function
	// TODO

//    while (cloud_f->points.size () > 0.3 * nr_points)
//      {
//        // Segment the largest planar component from the remaining cloud
//        //seg.setInputCloud (cloud_f);  //split the biggest plane of the rest PCL-Cloud
//        //seg.segment (*inliers, *coefficients);
//        if (inliers->indices.size () == 0)  //if the number of the PCL-Cloud is equal to 0, this means there is no PCL-Cloud now
//        {
//          std::cerr << "Could not estimate a planar model for the given dataset." << std::endl;
//          break;
//        }

        // Extract the inliers
        pcl::ExtractIndices<pcl::PointXYZ> extract;
        extract.setInputCloud (cloud_f);
        extract.setIndices (inliers);
        extract.setNegative (false);


        extract.filter (curr_table_pc);
        extract.setNegative(true);
            extract.filter(curr_clusters_pc);
        //std::cerr << "PointCloud representing the planar component: " << cloud_plane->width * cloud_plane->height << " data points." << std::endl;

//        //std::stringstream ss;
//        //ss << "table_scene_lms400_plane_" << i << ".pcd";
//        //writer.write<pcl::PointXYZ> (ss.str (), *cloud_plane, false);

//        // remove the inner points of the plane, extract the rest PCL-Cloud
//        extract.setNegative (true);
//        extract.filter (*cloud_f);
//        //cloud_filtered.swap (cloud_f);
//       //i++;
//      }


        // If you want to extract more than one plane you have to do a while


    //----


    // Publish biggest plane
	// TODO
	// Tips: 
  // - you can copy the pointcloud using pcl::copyPointCloud()
	// - Set the header frame_id to the pc2 header frame_id
	// - you can use pcl_conversions::toPCL() to convert the stamp from pc2 header to pointcloud header stamp
	// - to publish -> pub_plane_pc_.publish( pointcloud_variable.makeShared() )
    //----

    //sensor_msgs::PointCloud2::header ros_header = pc.header;
   // pcl::PCLHeader pcl_header;
//    pcl::PointCloud<pcl::PointXYZ> msg;
//    //pcl::copyPointCloud(*cloud_plane, msg);
//    //pcl_conversions::toPCL(msg.header, pc.header);
//    cloud_plane->header = pc.header;
//    pub_plane_pc_.publish(*cloud_plane);
    //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
     // viewer = simpleVis(*cloud_plane);
    pcl::toROSMsg(curr_table_pc,Out);
    pub_plane_pc_.publish(Out);

    // Publish other clusters
    // TODO similar to the previous publish
//    extract.setInputCloud (cloud_f);
//    extract.setIndices (inliers);
//    extract.setNegative (true);
//    extract.filter (curr_clusters_pc);
    pcl::toROSMsg(curr_clusters_pc,Out1);
    pub_clusters_pc_.publish(Out1);

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


