
cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 14)
project(lane_line_detector)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")
set( CMAKE_CXX_FLAGS "-g " )

find_package(OpenCV 4.1 REQUIRED)

include_directories(src)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB SOURCES "src/*.cpp") #src/*.h

add_executable(lane_line_detector src/data_processor.cpp src/image_proc.cpp src/lane_detector.cpp src/main.cpp)
target_link_libraries(lane_line_detector ${OpenCV_LIBS} )