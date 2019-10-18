cmake_minimum_required(VERSION 3.12)
project(SP19CLASSIFIER_TEST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")

add_executable(${PROJECT_NAME} test.cpp)
set(OpenCV_DIR /usr/local/include)
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
	message(STATUS "OpenCV library status:")
	message(STATUS "    version: ${OpenCV_VERSION}")
	message(STATUS "    libraries: ${OpenCV_LIBS}")
	message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
	include_directories(${OPENCV_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()


