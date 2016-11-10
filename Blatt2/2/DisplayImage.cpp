#include <iostream>
#include "opencv2/opencv.hpp"

int main(void)
{
  cv::VideoCapture cap;
  
  cv::namedWindow( "this is you!", CV_WINDOW_AUTOSIZE );
  cv::namedWindow( "this is you in gray!", CV_WINDOW_AUTOSIZE );
  
  if(!cap.open(0))
    return(0);
  for (;;)
  {
    cv::Mat frame,gray_frame;
    cap >> frame;
    cvtColor( frame, gray_frame, CV_BGR2GRAY );
    
    if ( frame.empty() ) break;
    cv::imshow("this is you!", frame);
    cv::imshow("this is you in gray!", gray_frame);
    if ( cv::waitKey(1) == 27) break;
  }
    
  return 0;  
}
