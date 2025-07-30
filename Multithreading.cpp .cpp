#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <string>

void processImage(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat image = cv::imread(inputPath);
    cv::Mat processedImage;
    cv::GaussianBlur(image, processedImage, cv::Size(15, 15), 0);
    cv::imwrite(outputPath, processedImage);
}

void processImagesInParallel(const std::vector<std::string>& inputPaths, const std::vector<std::string>& outputPaths) {
    std::vector<std::thread> threads;

    for (size_t i = 0; i < inputPaths.size(); ++i) {
        threads.emplace_back(processImage, inputPaths[i], outputPaths[i]);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}