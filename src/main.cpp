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
    
   std:string VideoPath = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/test.mp4";
   cv::VideoCapture cap(VideoPath);

   if(!cap.isOpened()){
       std::cout<<"Cannnot open Video";
       return -1;
   }
while (1){
    
    /*
    std::string imageName = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/input.jpg";
    cv::Mat img = imread( cv::samples::findFile( imageName, cv::IMREAD_COLOR )); // Load an image
    */
   cv::Mat img;
   cap >> img;
   
    // Check if image is loaded fine
    //namedWindow("Image", WINDOW_AUTOSIZE );
    //imshow("Image", img);
    //waitKey(5000);
    if( img.empty()) {
        printf(" Error opening image\n");
        printf(" No image selected\n");
        return -1;
    }
    
    //while(!img.empty()){
        DataProcessor dataProcessor;
        //Step1 : Select Yellow and White Lines 
        cv::Mat yellowwhite = dataProcessor.yellow_white_lines(img);
        //std::string yellowwhiteSTR = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/input.jpg";
       // cv::imwrite(yellowwhiteSTR, yellowwhite);
       /*
        namedWindow("Yellow White Image", WINDOW_AUTOSIZE );
        imshow("Yellow White Image", yellowwhite);
        waitKey(4000);
        */
        //step 2 : Apply grey scale to the yellow_white image
        
        cv::Mat greyscale = dataProcessor.rgb2greyscale(yellowwhite);
        /*
        namedWindow("GreyScale Image", WINDOW_AUTOSIZE );
        imshow("GreyScale Image", greyscale);
        waitKey(4000);
        */
        //Step 3: apply Gaussian blurr to the image
        cv::Mat gaussblurr = dataProcessor.gaussian_blur(greyscale);
        /*
        namedWindow("GaussianBlurr Image", WINDOW_AUTOSIZE );
        imshow("GaussianBlurr Image", gaussblurr);
        waitKey(4000);
        */
        ImageProc imageProcessor;
        //Step 4 : Apply canny edge detection to greyscale image
        cv::Mat cannyEdgeImage = imageProcessor.canny_edge(gaussblurr);//change this function definition
        //namedWindow("Canny Image", WINDOW_AUTOSIZE );
        //imshow("Canny Image", cannyEdgeImage);
        //waitKey(4000);
        //Step 5 : Polygon Mask/ Region of interest
        cv::Mat polygonMaskImage = imageProcessor.polygon_mask(cannyEdgeImage);
        //namedWindow("Masked Image", WINDOW_AUTOSIZE );
        //cv::imshow("Masked Image", polygonMaskImage);
        //waitKey(100);
        
        
        LaneDetector laneDetector;
        //Step 6 : Hough Lines Transform
        vector<cv::Vec4i> houghLaneLines = laneDetector.hough_line_transform(polygonMaskImage);

        
       // Step 7 : Left and right Lane lines (Generate left and right lane lines)
        std::vector<std::vector<cv::Vec4i> > lineSeparation = laneDetector.line_separation(houghLaneLines, cannyEdgeImage);
        std::vector<cv::Point> lanePoints = laneDetector.least_squares(lineSeparation, img);

        //Step 8 : Draw lane lines on the image
        cv::Mat laneLines = laneDetector.plotLines(img, lanePoints);
        //Step 8 : weighted image
        //Step 9: plot lines on image
        cv::namedWindow("Lane", WINDOW_AUTOSIZE);
        cv::imshow("Lane", laneLines);
        waitKey(10);


        
        ///Write the output to a file
        Size size = Size((int) cap.get(CAP_PROP_FRAME_WIDTH), (int) cap.get(CAP_PROP_FRAME_HEIGHT));
        int fourcc = cap.get(CAP_PROP_FOURCC);
        double fps = cap.get(CAP_PROP_FPS);
        bool isColor=true;

        cv::VideoWriter outputVideo;
        std::string Videooutputfile = "/home/karthik/Projects/CppND-Capstone-Hello-World/data/output.mp4";
        
        outputVideo.open(Videooutputfile, fourcc, fps, size, isColor);

        if(!outputVideo.isOpened()){
            cout<<("Cannot write the video file");
            return -1;
        }

        outputVideo.write(laneLines);

            //if(!outputVideo.read(laneLines))
            //cout<<"Cannot write frames to video");
        
        //cv::namedWindow("Lane", WINDOW_AUTOSIZE);
        //cv::imshow("Lane", outputVideo);
        //waitKey(10);
     }

    return 0;
}

