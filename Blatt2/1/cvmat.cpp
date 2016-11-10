#include <iostream>
#include "opencv2/opencv.hpp"

int main(void)
{
  /*<cv::Mat m0(2,2,CV_8UC1);
  std::cout << "m0 = \n " << m0 << std::endl;
  
  cv::Mat m1(2,2,CV_8UC3);
  std::cout << "m1 = \n " << m1 << std::endl;  
  
  cv::Mat m2(3,2,CV_8UC3, cv::Scalar(1,0,2));
  std::cout << "m2 = \n " << m2 << std::endl;  
    
  cv::Mat m3(2,2,CV_8UC3, cv::Scalar(126,0,255));
  std::cout << "m3 = \n " << m3 << std::endl; 
  
  cv::Mat m4(3,2,CV_8UC3, cv::Scalar(1,0,2));
  std::cout << "m4 = \n " << m4 << std::endl; 
  
  cv::Mat m5(2,2,CV_64FC3, cv::Scalar(1.1,0.1,2.1));
  std::cout << "m5 = \n " << m5 << std::endl; */
    
  cv::Mat m0(2,2,CV_8UC1, cv::Scalar(8));
  cv::Mat m_tmp(m0);
  
  std::cout << "m0 = \n " << m0 << std::endl;
  std::cout << "m_temp = \n " << m_tmp << std::endl;
  
  m0.at<uchar>(0,0) = 4;
  
  std::cout << "m0 = \n " << m0 << std::endl;
  std::cout << "m_temp = \n " << m_tmp << std::endl;
    
  return 0;  
}
