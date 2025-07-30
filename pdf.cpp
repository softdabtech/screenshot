#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-image.h>
#include <opencv2/opencv.hpp>
#include <string>

void saveImageAsPDF(const std::string& imagePath, const std::string& pdfPath) {
    // Загрузка изображения
    cv::Mat image = cv::imread(imagePath);

    // Преобразование OpenCV изображения в формат Poppler
    poppler::image popplerImage(image.cols, image.rows, poppler::image::format_enum::format_rgb24);
    memcpy(popplerImage.data(), image.data, image.total() * image.elemSize());

    // Создание PDF-документа
    poppler::document* doc = poppler::document::create();
    poppler::page* page = doc->create_page(popplerImage.width(), popplerImage.height());
    page->add_image(popplerImage, 0, 0);

    // Сохранение PDF
    doc->save(pdfPath);
    delete doc;
}