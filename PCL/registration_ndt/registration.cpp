#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>
#include <vector>
#include <pcl/registration/ndt.h>
#include <pcl/visualization/point_cloud_handlers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/passthrough.h>

int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr source (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr source_sampled (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr target (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr registered (new pcl::PointCloud<pcl::PointXYZ>);
  std::vector<int> indices;

  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../cloud001.pcd", *source) == -1)
  {
    PCL_ERROR ("Couldn't read the source cloud \n");
    return (-1);
  }
  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../cloud002.pcd", *target) == -1)
  {
    PCL_ERROR ("Couldn't read the target cloud \n");
    return (-1);
  }
  
  std::cerr << "Source before removing NaNs: " << source->width * source->height 
       << " data points (" << pcl::getFieldsList (*source) << ").\n";
       
  pcl::removeNaNFromPointCloud (*source, *source, indices);
  pcl::removeNaNFromPointCloud (*target, *target, indices);
  
  std::cerr << "Source after removing NaNs: " << source->width * source->height 
       << " data points (" << pcl::getFieldsList (*source) << ").\n";
       
       
       
  // Create the filtering object
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setLeafSize (0.1f, 0.1f, 0.1f);
  
  sor.setInputCloud (source);  
  sor.filter (*source_sampled);

  std::cerr << "Source after downsampling: " << source_sampled->width * source_sampled->height 
       << " data points (" << pcl::getFieldsList (*source_sampled) << ").\n";




  // Initializing Normal Distributions Transform (NDT).
  pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;

  // Setting scale dependent NDT parameters
  // Setting minimum transformation difference for termination condition.
  ndt.setTransformationEpsilon (0.01);
  // Setting maximum step size for More-Thuente line search.
  ndt.setStepSize (0.1);
  //Setting Resolution of NDT grid structure (VoxelGridCovariance).
  ndt.setResolution (0.5);

  // Setting max number of registration iterations.
  ndt.setMaximumIterations (35);

  // Setting point cloud to be aligned.
  ndt.setInputSource (source_sampled);
  // Setting point cloud to be aligned to.
  ndt.setInputTarget (target);

  // Set initial alignment estimate found using robot odometry.
  Eigen::AngleAxisf init_rotation(0.7, Eigen::Vector3f::UnitZ());
  Eigen::Translation3f init_translation(0.5, -0.3, -0.3);
  Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();

  // Calculating required rigid transform to align the input cloud to the target cloud.
  ndt.align (*registered, init_guess);

  std::cout << "Normal Distributions Transform has converged:" << ndt.hasConverged ()
            << " score: " << ndt.getFitnessScore () << std::endl;
  std::cout << "The final transformation matrix: \n" << ndt.getFinalTransformation () << std::endl;

  // Transforming unfiltered, input cloud using found transform.
  pcl::transformPointCloud (*source, *registered, ndt.getFinalTransformation ());


  std::cout << "Normal Distributions Transform has converged:" << ndt.hasConverged ()
            << " score: " << ndt.getFitnessScore () << std::endl;
  std::cout << "The final transformation matrix: \n" << ndt.getFinalTransformation () << std::endl;




  pcl::visualization::PCLVisualizer viewer ("Transformed source and Target");
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> registered_handler (registered, 255, 0, 0);
  // We add the point cloud to the viewer and pass the color handler
  viewer.addPointCloud (registered, registered_handler, "registered");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_handler (target, 0, 255, 0); // Red
  viewer.addPointCloud (target, target_handler, "target");
  
  viewer.addCoordinateSystem (1.0, "cloud", 0);
  viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "registered");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target");
  
  //viewer.showCloud(registered);
  while  (! viewer.wasStopped ())
  { 
    viewer.spinOnce ();
  }

  return (0);
}


















