#include <windows.h>
#include <gdiplus.h>
#include <string>

#pragma comment(lib, "gdiplus.lib")

void captureScreen(const std::string& outputPath) {
    // Инициализация GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Получение дескрипторов экрана
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    SelectObject(hDC, hBitmap);

    // Копирование экрана в HBITMAP
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    // Сохранение изображения
    Gdiplus::Bitmap bitmap(hBitmap, NULL);
    CLSID clsid;
    Gdiplus::GetEncoderClsid(L"image/png", &clsid);
    std::wstring wOutputPath(outputPath.begin(), outputPath.end());
    bitmap.Save(wOutputPath.c_str(), &clsid, NULL);

    // Очистка ресурсов
    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    Gdiplus::GdiplusShutdown(gdiplusToken);
}