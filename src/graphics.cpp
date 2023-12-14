#include "graphics.hpp"
#include <raylib.h>
#include <string>

Window::Window(int width, int height, int fps, bool useOptomizedMode, std::string title) {
    window_width = width;
    window_height = height;
    window_title = title;
    target_fps = fps;
    OptomizedMode = useOptomizedMode;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            VRAM[y][x] = 0x00000;
        }
    }

    InitWindow(window_width, window_height, window_title.c_str());
    SetTargetFPS(target_fps);
};

Window::~Window() {
    CloseWindow();
};

void Window::Redraw() {
    BeginDrawing();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, (Color){static_cast<unsigned char>((VRAM[y][x] >> 16) & 0xFF), static_cast<unsigned char>((VRAM[y][x] >> 8) & 0xFF), static_cast<unsigned char>(VRAM[y][x] & 0xFF), 255});
        }
    }
    EndDrawing();
};

bool Window::ShouldClose() {
    return WindowShouldClose();
};
