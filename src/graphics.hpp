#pragma once
#include <raylib.h>
#include <string>
#include "consts.hpp"

class Window {
private:
    int window_width;
    int window_height;
    std::string window_title;
    int target_fps;
public:
    uint32_t VRAM[HEIGHT][WIDTH];
    bool OptomizedMode;

    Window(int width, int height, int fps, bool useOptomizedMode, std::string title);
    ~Window();
    void Redraw();
    bool ShouldClose();
};
