#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <png.h>
#include <string>
#include <fstream>

void captureScreen(const std::string& outputPath) {
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);
    XWindowAttributes gwa;
    XGetWindowAttributes(display, root, &gwa);
    int width = gwa.width;
    int height = gwa.height;

    XImage* image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

    // Сохранение изображения в PNG
    FILE* fp = fopen(outputPath.c_str(), "wb");
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    for (int y = 0; y < height; y++) {
        png_write_row(png, (png_bytep)(image->data + y * image->bytes_per_line));
    }

    png_write_end(png, NULL);
    fclose(fp);

    XDestroyImage(image);
    XCloseDisplay(display);
}