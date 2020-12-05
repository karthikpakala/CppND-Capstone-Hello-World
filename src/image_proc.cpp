#include "image_proc.h"



using namespace cv;
using namespace std;

//step 4: any edge detection
cv::Mat ImageProc::canny_edge(Mat canny_input) { //change this function definition
    cv::Mat thresh_output, canny_output;
    cv::Canny(canny_input, canny_output, 140, 255);
    return canny_output;

}  
//step 5: polygon_mask
cv::Mat ImageProc::polygon_mask(Mat mask_input){
    cv::Mat mask_output;
    cv::Mat mask = cv::Mat::zeros(mask_input.size(), mask_input.type());

    cv::Point pts[4] = {cv::Point(240, 200), cv::Point(400, 200), 
                        cv::Point(720, 400), cv::Point(0, 540)};
   // cv::Point pts;
   // cv::Point pts[4] = {cv::Point(0, 720), cv::Point(550, 450), cv::Point(717, 450), cv::Point(1280, 720)};
    //cv::fillPoly(mask_input, pts, cv::Scalar(255, 255,255), 8, 0)
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 255, 255));
    cv::bitwise_and(mask_input, mask, mask_output);

    return mask_output;
    
}
