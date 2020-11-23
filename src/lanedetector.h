#ifndef LANE_DETECTOR_H
#define LANE_DETECTOR_H

#include <opencv2/core/mat.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/core/matx.hpp>

class LaneDetector{
    public:
    std::vector<cv::Vec4i>  hough_line_transform(cv::Mat);
    std::vector<std::vector<cv::Vec4i> > line_separation(std::vector<cv::Vec4i>, cv::Mat);
    std::vector<cv::Point> least_squares(std::vector<std::vector<cv::Vec4i> >, cv::Mat); 
    int plotLines(cv::Mat, std::vector<cv::Point>);
};

#endif
