#include "opencv2/opencv.hpp"
#include <iostream>

int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return 0;
  for(;;)
  {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) break;
    cv::imshow("this is you, smile! :)", frame);
    if (cv::waitKey(1) == 27) break;
  }
  return 0;
}
