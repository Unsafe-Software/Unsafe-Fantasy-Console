#include <iostream>
#include <raylib.h>
#include "config.hpp"
#include "consts.hpp"
#include "graphics.hpp"

int main(int, char**) {
    std::cout << "Booting up " << Config::Name << " " << Config::Version << ";" << std::endl;
    std::cout << Config::License << std::endl << std::endl;

    // Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, 60, false, TITLE);
    // while (!window->ShouldClose()) {
    //     window->Redraw();
    // }
}
