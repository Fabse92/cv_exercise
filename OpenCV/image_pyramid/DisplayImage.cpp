#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>
#include <vector>

using namespace cv;

/// Global variables
Mat src, up, down;
char* down_window = "Down Pyramids";
char* up_window = "Up Pyramids";
std::vector<cv::Mat> pyramid;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  cv::VideoCapture cap;
  if(!cap.open(0))
    return 0;

  /// Create window
  namedWindow( up_window, CV_WINDOW_AUTOSIZE );
  namedWindow( down_window, CV_WINDOW_AUTOSIZE );

  while( true )
  {
    cap >> src;
    if (src.empty()) break;

    int c;
    c = waitKey(10);

    if( (char)c == 27 )
      { break; }
      
    if( (char)c == 's' )
      {  
        for (int i = 0; i < 10; ++i)
        {
          pyrDown( src, down, Size( src.cols/2, src.rows/2 ) );
        } 
      }  
      
    pyrUp( src, up, Size( src.cols*2, src.rows*2 ) );
    pyrDown( src, down, Size( src.cols/2, src.rows/2 ) );

    imshow( up_window, up );
    imshow( down_window, down );
  }
  return 0;
}
