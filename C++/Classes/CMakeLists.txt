cmake_minimum_required(VERSION 2.8)
project( my_hello_class_project )

# Select type of build
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# Specify a greeter library
add_library( greeter Greeter.cpp )

# Specify executable to build
add_executable( hello hello.cpp )

# Link greeter library to our executable
target_link_libraries( hello greeter )
