#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>


/// Global variables

cv::Mat src, src_gray;
cv::Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  cv::blur( src_gray, detected_edges, cv::Size(3,3) );

  /// Canny detector
  cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = cv::Scalar::all(0);

  src.copyTo( dst, detected_edges);
  cv::imshow( window_name, dst );
 }

  
int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return 0;
  for(;;)
  {
    cap >> src;
    if (src.empty()) break;
    
    cv::cvtColor( src, src_gray, CV_BGR2GRAY );
    dst.create( src.size(), src.type() );
    
    cv::namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    cv::createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    
    /// Show the image
    CannyThreshold(0, 0);
    if (cv::waitKey(1) == 27) break;
  }
  return 0;
}
