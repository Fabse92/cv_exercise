cmake_minimum_required(VERSION 2.8)
project( my_hello_project )

# Select type of build
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# Specify executable to build
add_executable( hello hello.cpp )
add_executable( hello2 hello2.cpp )
