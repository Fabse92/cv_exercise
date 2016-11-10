cmake_minimum_required(VERSION 2.8)
project( cvmat )

find_package( OpenCV REQUIRED )

add_executable( cvmat cvmat.cpp )

target_link_libraries( cvmat ${OpenCV_LIBS} )
