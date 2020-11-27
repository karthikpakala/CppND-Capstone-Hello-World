#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <vector>
#include "data_processor.h"
#include "image_proc.h"
#include "lanedetector.h"
#include <fstream>

using namespace cv;
using namespace std;

/*

    Apply mask to select just pixels with yellow or white colour to detect the lanes
    Convert image to grayscale and apply slight Gaussian Blur.
    Apply Canny Edge Detector to get Edges
    Apply polygon mask to select region of interest
    Perform Hough Lines transformation to get lines on the image. Extrapolate and average
    the Hough lines to get a single solid line for each lane
    Draw both lane lines on original image and add Weight
*/


int main( int argc, char** argv )
{    // Loads an image
    std::string imageName = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/input.jpg";
    cv::Mat img = imread( cv::samples::findFile( imageName, cv::IMREAD_COLOR )); // Load an image
    // Check if image is loaded fine
    if( img.empty()) {
        printf(" Error opening image\n");
        printf(" No image selected\n");
        return -1;
    }

    while (!img.empty()){
        DataProcessor dataProcessor;
        cv::Mat yellowwhite = dataProcessor.yellow_white_lines(img);
        cv::Mat greyscale = dataProcessor.rgb2greyscale(yellowwhite);
        cv::Mat gaussblurr = dataProcessor.gaussian_blur(greyscale);

        ImageProc imageProcessor;
        cv::Mat cannyEdgeImage = imageProcessor.canny_edge(gaussblurr);
        cv::Mat polygonMaskImage = imageProcessor.polygon_mask(cannyEdgeImage);
        cv::imshow("polygon", polygonMaskImage);

        LaneDetector laneDetector;
       // vector<cv::Vec4i> finalImage = laneDetector.hough_line_transform(polygonMaskImage);
       //std::vector<cv::Vec4i> hough_lines = laneDetector.hough_line_transform(polygonMaskImage);
       //std::vector<std::vector<cv::Vec4i> > lines = laneDetector.line_separation(hough_lines, cannyEdgeImage);
       //std::vector<cv::Point> lane = laneDetector.least_squares(lines, gaussblurr);
       //int laneLines = laneDetector.plotLines(gaussblurr, lane);
    }
    return 0;
}
