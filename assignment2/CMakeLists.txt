cmake_minimum_required(VERSION 2.8)
project( Opencv_test )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/include)


#add_executable( Opencv_test  main.cpp)
#add_executable(Opencv_test v01_Select_box.cpp)
add_executable(Opencv_test v02_Find_center.cpp)
target_link_libraries( Opencv_test ${OpenCV_LIBS} )