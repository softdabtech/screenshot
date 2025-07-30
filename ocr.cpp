#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

void performOCR(const std::string& imagePath) {
    // Загрузка изображения
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    // Преобразование OpenCV изображения в Pix (формат Tesseract)
    Pix* pixImage = pixCreate(image.cols, image.rows, 8);
    for (int y = 0; y < image.rows; y++) {
        memcpy(pixGetData(pixImage) + y * pixGetWpl(pixImage) * 4, image.ptr(y), image.cols);
    }

    // Инициализация Tesseract
    tesseract::TessBaseAPI tess;
    if (tess.Init(NULL, "eng")) { // Используем английский язык
        std::cerr << "Could not initialize tesseract.\n";
        return;
    }

    tess.SetImage(pixImage);
    char* outText = tess.GetUTF8Text();

    // Вывод распознанного текста
    std::cout << "Распознанный текст:\n" << outText << std::endl;

    // Очистка ресурсов
    tess.End();
    pixDestroy(&pixImage);
    delete[] outText;
}