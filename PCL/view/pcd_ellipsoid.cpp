#include  <pcl/io/pcd_io.h>
#include  <pcl/point_types.h>
#include  <pcl/visualization/cloud_viewer.h>
#include  <cmath>
#include  <iostream>

int  main(int argc , char* argv [])
{
  const  float pi = 3.14159265358979f;
  const  float  two_pi = 2*pi;
  // The  ellipsoid  center  at (x0,y0,z0)
  const  float x0 = 0.0f, y0 = 0.0f, z0 = 0.0f;
  //  ellipsoid  semi -axes  lengths (for  sphere , a=b=c)
  const  float a = 1.0f, b = 1.0f, c = 1.0f;
  //  theta: azimuthal  coordinate , 0 to 2*pi
  // psi: polar  coordinate , 0 to pi
  const  float  azimuthal_resolution = pi / 60.0f;
  const  float  polar_resolution = pi / 60.0f;
  pcl::PointCloud <pcl::PointXYZ >::Ptr  cloud(new  pcl::PointCloud <pcl::PointXYZ >);
  for (float  theta =0.0f; theta <= two_pi; theta += azimuthal_resolution)
  {
    for (float  psi =0.0f; psi <=pi; psi+= polar_resolution)
    {
      const  float x=x0+a*std::cos(theta)*std::sin(psi);
      const  float y=y0+b*std::sin(theta)*std::sin(psi);
      const  float z=z0+c*std::cos(psi);
      cloud ->push_back(pcl:: PointXYZ(x,y,z));
    }
  }
  std::cout  << "Saving cloud ..." << std::endl;
  pcl::io:: savePCDFileASCII ("ellipsoid_pcd.pcd", *cloud);
  std::cout  << "Saved " << cloud ->points.size () << " data points to ellipsoid_pcd." << std::endl;
  // See  the  output
  pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
  viewer.showCloud(cloud);
  while  (! viewer.wasStopped ())
  { //no -op  until  viewer  stopped
  }
  return  0;
}
