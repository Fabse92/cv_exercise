#include <iostream>
#include "opencv2/opencv.hpp"

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 1000;
int MAX_KERNEL_LENGTH = 31;

cv::Mat src,gray_frame,dst;
char window_name[] = "Filter Demo 1";

/// Function headers
int display_caption( char* caption );
int display_dst( int delay );



void Threshold_Demo( int, void* );

int main(void)
{
  cv::VideoCapture cap;
  
  if(!cap.open(0))
    return(0);
  for (;;)
  {
    cap >> src;
    cv::cvtColor( src, gray_frame, CV_BGR2GRAY );
    
    if( display_caption( "Original Image" ) != 0 ) 
    { 
      return 0; 
    }

    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 ) 
    { 
      return 0; 
    }

    /// Applying Homogeneous blur
    if( display_caption( "Homogeneous Blur" ) != 0 ) 
    { 
      return 0; 
    }
 
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    { 
      blur( src, dst, cv::Size( i, i ), cv::Point(-1,-1) );
      if( display_dst( DELAY_BLUR ) != 0 ) 
      {
        return 0; 
      } 
    }
    
     /// Applying Gaussian blur
    if( display_caption( "Gaussian Blur" ) != 0 ) 
    { 
      return 0; 
    }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
      GaussianBlur( src, dst, cv::Size( i, i ), 0, 0 );
      if( display_dst( DELAY_BLUR ) != 0 ) 
      { 
        return 0; 
      } 
    }

    /// Applying Median blur
    if( display_caption( "Median Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
       { medianBlur ( src, dst, i );
         if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

    /// Applying Bilateral Filter
    if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
       { bilateralFilter ( src, dst, i, i*2, i/2 );
         if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }
    
    
    display_caption( "End: Press a key!" );
    
  }
    
  return 0;  
}

int display_caption( char* caption )
{
  dst = cv::Mat::zeros( src.size(), src.type() );
  cv::putText( dst, caption,
          cv::Point( src.cols/4, src.rows/2),
          CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255) );

  cv::imshow( window_name, dst );
  int c = cv::waitKey( DELAY_CAPTION );
  if( c >= 0 ) { return -1; }
  return 0;
}

int display_dst( int delay )
{
  cv::imshow( window_name, dst );
  int c = cv::waitKey ( delay );
  if( c >= 0 ) { return -1; }
  return 0;
}






