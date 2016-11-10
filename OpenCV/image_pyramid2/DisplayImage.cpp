#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>
#include <vector>

using namespace cv;

/// Global variables
Mat src, down, tmp;
char* stream_window = "Video stream";
char* pyramid_window = "Pyramid";
std::vector<cv::Mat> pyramid;
int current = 0;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  cv::VideoCapture cap;
  if(!cap.open(0))
    return 0;

  /// Create window
  namedWindow( stream_window, CV_WINDOW_AUTOSIZE );
  namedWindow( pyramid_window, CV_WINDOW_AUTOSIZE );

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
        tmp = src.clone();
        for (int i = 0; i < 9; ++i)
        {
          pyramid.push_back(tmp);
          pyrDown( tmp, tmp, Size( tmp.cols/2, tmp.rows/2 ) );    
        } 
      }  
    if( (char)c == 'n' )
    {
      if (current < 8)
      {
        ++current;
        imshow( pyramid_window, pyramid[current] ); 
      }    
    }
    if( (char)c == 'p' )
    {
      if (current > 0)
      {
        --current;
        imshow( pyramid_window, pyramid[current] );
      }
    }
      
    imshow( stream_window, src );    
  }
  return 0;
}
