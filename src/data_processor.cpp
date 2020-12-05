#include "data_processor.h"

using namespace std;
using namespace cv;
cv::Mat DataProcessor::read_image(std::string filepath){
    cv::Mat img;
    string image_path = cv::samples::findFile(filepath);
    img = cv::imread(filepath, IMREAD_COLOR);
    return img;
}
//step 1: read data
cv::Mat DataProcessor::yellow_white_lines(cv::Mat input_image){
    cv::Mat converted_hls, yellow_white;
    cv::cvtColor(input_image, converted_hls, COLOR_BGR2HLS);
    cv::Scalar lower_white = cv::Scalar(0, 200, 0);
    cv::Scalar upper_white = cv::Scalar(255, 255, 255);
    cv::Scalar lower_yellow = cv::Scalar(10, 0, 100);
    cv::Scalar upper_yellow = cv::Scalar(40, 255, 255);

    cv::Mat white_mask, yellow_mask, mask_edges, mask;
    cv::inRange(converted_hls, lower_white, upper_white, white_mask);
    cv::inRange(converted_hls, lower_yellow, upper_yellow, yellow_mask);
    cv::bitwise_or(white_mask, yellow_mask, mask_edges);
    cv::bitwise_and(input_image, input_image, yellow_white, mask_edges);
    return yellow_white;
}
//step 2:  convert to greyscale
cv::Mat DataProcessor::rgb2greyscale(cv::Mat greyinput){
    cv::Mat rgb2grey;
    cv::cvtColor(greyinput, rgb2grey, COLOR_BGR2GRAY, 0);
    return rgb2grey;
}
//step 3: gaussian blurr
cv::Mat DataProcessor::gaussian_blur(cv::Mat rgb2grey){
    cv::Mat gauss_blurr;
    cv::GaussianBlur(rgb2grey, gauss_blurr, cv::Size(3,3), 0, 0, BORDER_DEFAULT);
    return gauss_blurr;
}
