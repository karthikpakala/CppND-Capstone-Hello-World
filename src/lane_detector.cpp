
#include "lane_detector.h"


using namespace cv;
using namespace std;

//step 6; Perform Hough Lines transformation to get lines on the image. s
std::vector<cv::Vec4i> LaneDetector::hough_line_transform(cv::Mat img_mask){
    vector<cv::Vec4i> lines;
    cv::Mat color_lines;
    HoughLinesP(img_mask, lines, 2, CV_PI/180, 50, 50, 150);
    cv::cvtColor(img_mask, color_lines, COLOR_GRAY2BGR);

    for(size_t i = 0; i < lines.size(); i++)
    {
        line(color_lines, Point(lines[i][0], lines[i][1]),
        Point(lines[i][2], lines[i][3]), Scalar(0,0, 255), 2, 8); 
    }
    namedWindow("Hough Image", WINDOW_AUTOSIZE );
    cv::imshow("Hough Image", color_lines);
    waitKey(10);
    
    return lines;
}
//process and output lane lines
std::vector<std::vector<cv::Vec4i> > LaneDetector::line_separation(std::vector<cv::Vec4i> lines, cv::Mat &image_edges) {
    std::vector<std::vector<cv::Vec4i> > output;
    size_t j = 0;
    cv::Point init;
    cv::Point finall;
    double slope_thres = 0.3;
    std::vector<double> slopes;
    std::vector<cv::Vec4i> selected_lines;
    std::vector<cv::Vec4i> right_lines, left_lines;

    for(auto i : lines){
        init = cv::Point(i[0], i[1]);
        finall = cv::Point(i[2], i[3]);

        double slope = (static_cast<double>(finall.y) - static_cast<double>(init.y))/(static_cast<double>(finall.x) - static_cast<double>(init.x) + 0.00001);

        if(std::abs(slope) > slope_thres){
            slopes.push_back(slope);
            selected_lines.push_back(i);
        }
    }

    double image_center = static_cast<double>(image_edges.cols/2) ;
    while(j < selected_lines.size()){
        init = cv::Point(selected_lines[j][0], selected_lines[j][1]);
        finall = cv::Point(selected_lines[j][2], selected_lines[j][3]);

        if(slopes[j] > 0 && finall.x > image_center && init.x > image_center){
            right_lines.push_back(selected_lines[j]);
            bool right_flag = true;
        }
        else if (slopes[j] < 0 && finall.x < image_center && init.x < image_center){
            left_lines.push_back(selected_lines[j]);
            bool left_flag = true;
        }
        j++;
    }
    output.push_back(left_lines); //failing here
    output.push_back(right_lines);

    return output;
}
//eorror with the handling of input points and line construction. Need to fix that.
std::vector<cv::Point> LaneDetector::least_squares(std::vector<std::vector<cv::Vec4i> > right_left_lines, cv::Mat &inputImage) {
    
    std::vector<cv::Point> output(4);
    cv::Point right_init;
    cv::Point right_final;
    cv::Point left_init;
    cv::Point left_final;
    cv::Vec4d right_line;
    cv::Vec4d left_line;
    std::vector<cv::Point> right_pts;
    std::vector<cv::Point> left_pts;
    double right_m, left_m;
    cv::Point right_b, left_b;

    if(bool right_flag = true) {
        for(auto i : right_left_lines.at(0)) {
            right_init = cv::Point(i[0], i[1]);
            right_final = cv::Point(i[2], i[3]);

            right_pts.push_back(right_init);
            right_pts.push_back(right_final);
        }

        if(right_pts.size() > 0) {
            cv::fitLine(right_pts, right_line, cv::DIST_L2, 0, 0.02, 0.02);
            right_m = right_line[1] / right_line[0];
            right_b = cv::Point(right_line[2], right_line[3]);
        }
    }

    if(bool left_flag = true){
        for(auto j : right_left_lines.at(1)) {
            left_init = cv::Point(j[0], j[1]);
            left_final = cv::Point(j[2], j[3]);
 
            left_pts.push_back(left_init);
            left_pts.push_back(left_final);
        }
         if(left_pts.size() > 0) {
             cv::fitLine(left_pts, left_line, cv::DIST_L2, 0, 0.02, 0.02);
             left_m = left_line[1] / left_line[0];
             left_b = cv::Point(left_line[2], left_line[3]);
         }
    }
    int init_y = inputImage.rows;
    int final_y = 470;

    double right_init_x = ((init_y - right_b.y) / right_m) + right_b.x;
    double right_final_x = ((final_y - right_b.y) / right_m) + right_b.x;

    double left_init_x = ((init_y - left_b.y) / left_m) + left_b.x;
    double left_final_x = ((final_y - left_b.y) / left_m) + left_b.x;

    output[0] = cv::Point(right_init_x, init_y);
    output[1] = cv::Point(right_final_x, final_y);
    output[2] = cv::Point(left_init_x, init_y);
    output[3] = cv::Point(left_final_x, final_y);

    return output;
}


cv::Mat LaneDetector::plotLines(cv::Mat &inputImage, std::vector<cv::Point> lanePoint) {
    cv::Point rightLinespt1, rightLinespt2, leftLinespt1, leftLinespt2;
    cv::Mat output;
    
    inputImage.copyTo(output);
    
    leftLinespt1 = lanePoint.at(0);
    leftLinespt2 = lanePoint.at(1);
    rightLinespt1 = lanePoint.at(2);
    rightLinespt2 = lanePoint.at(3);

    cv::addWeighted(output, 0.3, inputImage, 1.0 - 0.3, 0, inputImage);


       for(size_t i = 0; i < lanePoint.size(); i++)
    {
        line(output, leftLinespt1, leftLinespt2, Scalar(0,0, 255), 5, 8); 
        line(output, rightLinespt1 , rightLinespt2, Scalar(0,0, 255), 5, 8); 
        //Right lane is not populating the vector array, so SEGFAULT in the program/// issue with the right lane line vector not populating in lane
        //line(output, Point(rightLines[i][0], rightLines[i][1]), Point(rightLines[i][2], rightLines[i][3]), Scalar(0,0, 255), 5, 8); 
        //line(output, Point(leftLines[i][0], leftLines[i][1]), Point(leftLines[i][2], leftLines[i][3]), Scalar(0,0, 255), 5, 8); 
    }
    
    return output;
}