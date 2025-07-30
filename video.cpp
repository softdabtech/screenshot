#include <cstdlib>
#include <string>

void recordScreen(const std::string& outputPath, int duration) {
    std::string command = "ffmpeg -f x11grab -video_size 1920x1080 -i :0.0 -t " + std::to_string(duration) + " -r 30 " + outputPath;
    system(command.c_str());
}