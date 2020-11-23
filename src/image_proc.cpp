#include <opencv2/highgui.hpp>
#include "image_proc.h"
#include <opencv2/core/types.hpp>

#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

//step 4: any edge detection
cv::Mat ImageProc::canny_edge(Mat canny_input) {
    cv::threshold(canny_output, thresh_output, 140,255, cv::THRESH_BINARY);

    anchor = cv::Point(-1, -1);
    kernel = cv::Mat(1,3, CV_32F);
    kernel.at<float>(0.0) = -1;
    kernel.at<float>(0,1) = 0;
    kernel.at<float>(0.2) = 1;

    cv::filter2D(thresh_output, canny_output, -1, kernel, anchor, 0, cv::BORDER_DEFAULT);

    return canny_output;

}  
//step 5: polygon_mask
cv::Mat ImageProc::polygon_mask(Mat mask_input){
    cv::Mat mask_output;
    cv::Mat mask = cv::Mat::zeros(mask_input.size(), mask_input.type());

    cv::Point pts[4] = {cv::Point(210, 720), cv::Point(550, 450), cv::Point(717, 450), cv::Point(1200, 720)};
   // cv::Point pts;

    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));
    cv::bitwise_and(mask_input, mask, mask_output);

    return mask_output;
    
}
