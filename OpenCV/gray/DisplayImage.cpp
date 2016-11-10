#include "opencv2/opencv.hpp"
#include <iostream>


int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return 0;
  for(;;)
  {
    cv::Mat src, gray_image;
    cap >> src;
    if (src.empty()) break;
    
    cvtColor( src, gray_image, CV_BGR2GRAY );
    
    //cv::imshow("this is you, smile! :)", src);
    //cv::namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Gray image", gray_image );
    if (cv::waitKey(1) == 27) break;
  }
  return 0;
}
