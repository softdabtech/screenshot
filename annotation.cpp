#include <opencv2/opencv.hpp>
#include <string>

void addAnnotation(const std::string& inputPath, const std::string& outputPath) {
    cv::Mat image = cv::imread(inputPath);

    // Добавление текста
    cv::putText(image, "Annotation", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

    // Добавление стрелки
    cv::arrowedLine(image, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(255, 0, 0), 2);

    cv::imwrite(outputPath, image);
}