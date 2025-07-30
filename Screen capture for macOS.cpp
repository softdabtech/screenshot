#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <string>

void captureScreen(const std::string& outputPath) {
    CGImageRef screenshot = CGDisplayCreateImage(kCGDirectMainDisplay);
    CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFSTR("screenshot.png"), kCFURLPOSIXPathStyle, false);
    CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
    CGImageDestinationAddImage(destination, screenshot, NULL);
    CGImageDestinationFinalize(destination);
    CFRelease(destination);
    CFRelease(url);
    CGImageRelease(screenshot);
}