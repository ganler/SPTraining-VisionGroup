cmake_minimum_required(VERSION 2.8)
project( l8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( l8 main.cpp )

target_link_libraries( l8 ${OpenCV_LIBS} )
