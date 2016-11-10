#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char** argv)
{
  int x,y;
  cv::Mat image;
  cv::Vec3b intensity;
  
  image = cv::imread(argv[1]);
  cv::imshow("Grav Image", image);
  
  cv::waitKey(0);
    
  x = 200;
  y = 100;  
  intensity = image.at<cv::Vec3b>(y,x);    
  std::cout << intensity << std::endl;
  
  x = 100;
  y = 200;  
  intensity = image.at<cv::Vec3b>(y,x);    
  std::cout << intensity << std::endl;
    
  return 0;  
}
