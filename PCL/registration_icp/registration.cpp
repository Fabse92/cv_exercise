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
#include <pcl/registration/icp.h>
#include <pcl/visualization/point_cloud_handlers.h>
#include <pcl/visualization/pcl_visualizer.h>

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



  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  // Set the input source and target
  icp.setInputSource (source_sampled);
  icp.setInputTarget (target);

  // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
  icp.setMaxCorrespondenceDistance (0.05);
  // Set the maximum number of iterations (criterion 1)
  icp.setMaximumIterations (50);
  // Set the transformation epsilon (criterion 2)
  icp.setTransformationEpsilon (1e-8);
  // Set the euclidean distance difference epsilon (criterion 3)
  icp.setEuclideanFitnessEpsilon (1);
  // Perform the alignment
  icp.align (*registered);
  // Obtain the transformation that aligned cloud_source to cloud_source_registered
  Eigen::Matrix4f transformation = icp.getFinalTransformation ();

  std::cout << "The registration has converged:" << icp.hasConverged() << " The fitness score: " << icp.getFitnessScore(0.05) << std::endl;
  std::cout << "The final transformation matrix: \n" << transformation << std::endl;

  std::cout << "Now with initial guess." << std::endl;
  
  Eigen::AngleAxisf init_rotation(0.7, Eigen::Vector3f::UnitZ());
  Eigen::Translation3f init_translation(0.5, -0.3, -0.3);
  Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();
  
   
  icp.align (*registered, init_guess);
  transformation = icp.getFinalTransformation ();
  
  std::cout << "The registration has converged:" << icp.hasConverged() << " The fitness score: " << icp.getFitnessScore(0.05) << std::endl;
  std::cout << "The final transformation matrix: \n" << transformation << std::endl;

  std::cout << "Now with full resolution source." << std::endl;
  icp.setInputSource (source);
  icp.align (*registered, transformation);
  transformation = icp.getFinalTransformation ();
  
  std::cout << "The registration has converged:" << icp.hasConverged() << " The fitness score: " << icp.getFitnessScore(0.05) << std::endl;
  std::cout << "The final transformation matrix: \n" << transformation << std::endl;


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


















