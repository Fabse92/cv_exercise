#include <iostream>
#include "opencv2/opencv.hpp"

int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return(0);
  for (;;)
  {
    cv::Mat frame;
    cap >> frame;
    if ( frame.empty() ) break;
    cv::imshow("this is you!", frame);
    if ( cv::waitKey(1) == 27) break;
  }
    
  return 0;  
}
