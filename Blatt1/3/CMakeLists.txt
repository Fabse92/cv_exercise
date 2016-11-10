cmake_minimum_required(VERSION 2.8)
project( cuboid_project )

# Select type of build
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# Specify a greeter library
add_library( cuboid Cuboid.cpp )

# Specify executable to build
add_executable( test test_program.cpp )

# Link greeter library to our executable
target_link_libraries( test cuboid )
