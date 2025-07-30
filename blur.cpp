#include <opencv2/opencv.hpp>
#include <string>

void applyBlur(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat image = cv::imread(inputPath);
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(15, 15), 0);
    cv::imwrite(outputPath, blurredImage);
}