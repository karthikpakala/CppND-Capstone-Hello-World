#include "data_processor.h"

using namespace std;
using namespace cv;
//step 1: read data
cv::Mat DataProcessor::read_image(std::string filepath){
    cv::Mat img;
    string image_path = cv::samples::findFile(filepath);
    img = cv::imread(filepath, IMREAD_COLOR);
    return img;
}

cv::Mat DataProcessor::yellow_white_lines(cv::Mat input_image){
    cv::Scalar lower_white = cv::Scalar(0, 200, 0);
    cv::Scalar upper_white = cv::Scalar(255, 255, 255);
    cv::Scalar lower_yellow = cv::Scalar(10, 0, 100);
    cv::Scalar upper_yellow = cv::Scalar(40, 255, 255);

    cv::Mat white_mask, yellow_mask, mask_edges;
    cv::inRange(input_image, lower_white, upper_white, white_mask);
    cv::inRange(input_image, lower_yellow, upper_yellow, yellow_mask);

    cv::bitwise_or(white_mask, yellow_mask, mask_edges);
    //cv::bitwise_and()
    return mask_edges;
}
//step 2:  convert to greyscale
cv::Mat DataProcessor::rgb2greyscale(cv::Mat output){
    cv::Mat rgb2grey;
    cv::cvtColor(output, rgb2grey, COLOR_BGR2GRAY);
    return rgb2grey;
}
//step 3: gaussian blurr
cv::Mat DataProcessor::gaussian_blur(cv::Mat rgb2grey){
    cv::Mat gauss_blurr;
    cv::GaussianBlur(rgb2grey, gauss_blurr, cv::Size(3,3), 0, 0);
    return gauss_blurr;
}
