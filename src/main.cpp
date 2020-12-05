#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <vector>
#include "data_processor.h"
#include "image_proc.h"
#include "lane_detector.h"
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
    std::string imageName = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/inputImage.png";
    cv::Mat img = imread( cv::samples::findFile( imageName, cv::IMREAD_COLOR )); // Load an image
    // Check if image is loaded fine
        //namedWindow("Image", WINDOW_AUTOSIZE );
        //imshow("Image", img);
        //waitKey(0);
    if( img.empty()) {
        printf(" Error opening image\n");
        printf(" No image selected\n");
        return -1;
    }
   // namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", img);
   // waitKey(0);
    while (!img.empty()){
        
        DataProcessor dataProcessor;
        //Step1 : Select Yellow and White Lines 
        cv::Mat yellowwhite = dataProcessor.yellow_white_lines(img);
        //std::string yellowwhiteSTR = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/input.jpg";
       // cv::imwrite(yellowwhiteSTR, yellowwhite);
       // namedWindow("Yellow White Image", WINDOW_AUTOSIZE );
        //imshow("Yellow White Image", yellowwhite);
        //waitKey(10);
        //step 2 : Apply grey scale to the yellow_white image
        
        cv::Mat greyscale = dataProcessor.rgb2greyscale(yellowwhite);
        //namedWindow("GreyScale Image", WINDOW_AUTOSIZE );
        //imshow("GreyScale Image", greyscale);
        //waitKey(10);
        
        //Step 3: apply Gaussian blurr to the image
        cv::Mat gaussblurr = dataProcessor.gaussian_blur(greyscale);
        //namedWindow("GaussianBlurr Image", WINDOW_AUTOSIZE );
        //imshow("GaussianBlurr Image", gaussblurr);
        //waitKey(10);
        
        ImageProc imageProcessor;
        //Step 4 : Apply canny edge detection to greyscale image
        cv::Mat cannyEdgeImage = imageProcessor.canny_edge(gaussblurr);//change this function definition
        //namedWindow("Canny Image", WINDOW_AUTOSIZE );
        //imshow("Canny Image", cannyEdgeImage);
        //waitKey(10);
        //Step 5 : Polygon Mask/ Region of interest
        cv::Mat polygonMaskImage = imageProcessor.polygon_mask(cannyEdgeImage);
        namedWindow("Masked Image", WINDOW_AUTOSIZE );
        cv::imshow("Masked Image", polygonMaskImage);
        waitKey(10);
        
        
        LaneDetector laneDetector;
        //Step 6 : Hough Lines Transform
        vector<cv::Vec4i> finalImage = laneDetector.hough_line_transform(polygonMaskImage);
        namedWindow("Hough Image", WINDOW_AUTOSIZE );
        cv::imshow("Hough Image", finalImage);
        waitKey(10);
       // std::vector<cv::Vec4i> hough_lines = laneDetector.hough_line_transform(polygonMaskImage);
       // Step 7 : Left and right Lane lines (Generate left and right lane lines)
       // std::vector<std::vector<cv::Vec4i> > lines = laneDetector.line_separation(hough_lines, cannyEdgeImage);
        //Least Squares???
        //std::vector<cv::Point> lane = laneDetector.least_squares(lines, gaussblurr);
        //Step 8 : Draw lane lines on the image
        //int laneLines = laneDetector.plotLines(gaussblurr, lane);
        //Step 8 : weighted image
        //Step 9: plot lines on image
        
     }
    return 0;
}

