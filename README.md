# CPPND: Capstone Lane Detector

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* opencv >= 4.2
   * The installation instructions for linux are contained within the following link:
     https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html
   



## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./lane_line_detector


Project Description and Structure.
1. The project is built to detect lane lines on the road using opencv libraray.
2. It extensively uses functions/classes from opencv library for data processing, plotting and read/write functions into image and video files.
3. The functions primarily work with single frames one at a time, wherein each frame is processed by using different opencv methods to get the desired output.
4. The project is structured into the following classes and coresponding .ccp/.h files under the project folder: 
   1.  data_processor.cpp
       This class contains all the functions that are related to data processing of thhe input data. The following are the steps involved in data processing and        
       the corresponding functions names:
       1. yellow_white_lanes : Extracts just the yellow and white pixels from the input image.
       2. rb2greyscale : Converts the colored image into a greyscale image
       3. gaussian_blurr : Applies gaussiar blurr on the resulting image from gaussian blurr above
   2. image_proc.cpp
       1. canny_edge : Applies the canny edge function from opencv library to extract the edges from the resulting image that is processed in the 
          data_processor.cpp
       2. polygon_mask : applies a polygon mask by construction a bounding box on the image to eliminate all other pixels from the image other than the lane lines 
          that are within the region of interest.
   3.lane_detector.cpp
       1. hough_line_transform : Applies hough line transform on the resulting image fom image_proc.cpp whih will result in lane detection from the image. 
       2. line_separator : Separates the detected lane lines into left and right lane lines.
       3. least_squares : Applies least squares function on the separated lane lines to generate a fitted line on either of the separated lane lines to generate 
          individul lane lines on each side.
   4. main.cpp
       main.cpp contains the instantiates all the functions sequentially to create objects that are generated out of each of the functions to pass on the object 
       to the next function and so on to generate the outputand store it in a file at the end of the loop. 

Expected behavior/output: 
The output of the program contains lane lines being plotted on the original video. lane lines are continually updated as the video progresses showing that the program is working in a itetarive way to detect lane lines and plot them in te original video.  
   
Ruberic Points : 
1. main.cpp : 
     1. The project reads data from a file and process the data, or the program writes data to  
     a file. (Line 30, Line 129)
     2. The project demonstrates an understanding of C++ functions and control structures.
     (Line 26, 36, 49, 124)
     3. The project accepts user input and processes the input. (Line 30, 43)
     
2. data_processor.cpp/data_procssor.h:
     1. The project uses Object Oriented Programming techniques. (data_processor.h(Line 14), 
     2. Classes use appropriate access specifiers for class members. (data_processor.h(Line 
     15, 19))
     3. The project makes use of references in function declarations. (data_processor.h (Line 
     12))
     
3. image_proc.cpp/image_proc.h : 
     1. The project uses Object Oriented Programming techniques. (image_proc.h (Line 14)), 
     2. Classes use appropriate access specifiers for class members. (image_proc(Line 15, 18)
     
4. lane_detector.cpp/lane_detector.h : 
     1. The project uses Object Oriented Programming techniques. (lane_detector.h(Line 16)
     2. The project makes use of references in function declarations. (lane_detector.h (Line   
     19, 20)
     
5. Doeumentation in README.md : 
     1. Classes abstract implementation details from their interfaces.(the function description covers the function intent and behavior. Hence this ruberic point is covered as a part of the documentation)
     
