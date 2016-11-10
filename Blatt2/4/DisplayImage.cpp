#include <iostream>
#include "opencv2/opencv.hpp"

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

char* window_name = "Threshold Demo";
char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

cv::Mat frame,gray_frame,dst;

void Threshold_Demo( int, void* );

int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return(0);
  for (;;)
  {
    cap >> frame;
    cv::cvtColor( frame, gray_frame, CV_BGR2GRAY );
    
    cv::createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );
    cv::createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );
                  
    Threshold_Demo( 0, 0 );
    
    if ( frame.empty() ) break;
    cv::imshow( window_name, dst );
    if ( cv::waitKey(1) == 27) break;
  }
    
  return 0;  
}

void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( gray_frame, dst, threshold_value, max_BINARY_value,threshold_type );
  
}
