#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/types.hpp>
#include<opencv2/core.hpp>

#include <stdio.h>
#include <iostream>

class DataProcessor {
    public: 
    cv::Mat read_image(std::string); //read file to process it.
    cv::Mat yellow_white_lines(cv::Mat &input_image); //identify yellow and whiles areas in the images
    cv::Mat rgb2greyscale(cv::Mat); //convert the image into a greyscale image
    cv::Mat gaussian_blur(cv::Mat); //apply gaussian blurr
    private:
    cv::Mat output, rgb2grey, gauss_blurr;

};
#endif