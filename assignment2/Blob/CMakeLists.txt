cmake_minimum_required(VERSION 2.8)
project( l7 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( l7 main.cpp )

target_link_libraries( l7 ${OpenCV_LIBS} )
