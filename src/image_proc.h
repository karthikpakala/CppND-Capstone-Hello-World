#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>
#include <stdio.h>

class ImageProc {
    public:
    cv::Mat canny_edge(cv::Mat); //canny edge detector
    cv::Mat polygon_mask(cv::Mat);
    private:
    cv::Mat canny_output, thresh_output, kernel, mask_input;
    cv::Point anchor; 
    //apply polygon mask to the resulting image.
};


#endif

