cmake_minimum_required(VERSION 2.8)
project( cvload )

find_package( OpenCV REQUIRED )

add_executable( cvload cvload.cpp )

target_link_libraries( cvload ${OpenCV_LIBS} )
