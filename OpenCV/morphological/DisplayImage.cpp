#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

int threshold_value = 100;
int threshold_type = 2;;
int const max_value = 255;
int const max_BINARY_value = 255;

/** Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );
void Threshold( int, void* );

/** @function main */
int main( int argc, char** argv )
{  
  /// Load an image
  cv::VideoCapture cap;
  
  /// Create windows
  namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
  namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
  
  if(!cap.open(0))
    return 0;
  for(;;)
  {
    cap >> src;
    if (src.empty()) break;
    
    cvtColor( src, src, CV_BGR2GRAY );
    threshold( src, src, threshold_value, max_BINARY_value,threshold_type );
    
    createTrackbar( "Threshold", "Erosion Demo",
                  &threshold_value,
                  max_value, Threshold );

    /// Create Erosion Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
                    &erosion_elem, max_elem,
                    Erosion );

    createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                    &erosion_size, max_kernel_size,
                    Erosion );

    /// Create Dilation Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
                    &dilation_elem, max_elem,
                    Dilation );

    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
                    &dilation_size, max_kernel_size,
                    Dilation );

    /// Default start
    Erosion( 0, 0 );
    Dilation( 0, 0 );

    if (cv::waitKey(1) == 27) break;
  }
  return 0;
}

/**  @function Erosion  */
void Erosion( int, void* )
{
  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  erode( src, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
}

/** @function Dilation */
void Dilation( int, void* )
{
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  /// Apply the dilation operation
  dilate( src, dilation_dst, element );
  imshow( "Dilation Demo", dilation_dst );
}

void Threshold( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( src, src, threshold_value, max_BINARY_value,threshold_type );
}
