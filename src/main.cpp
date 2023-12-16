#include <iostream>
#include <raylib.h>
#include "config.hpp"
#include "consts.hpp"
#include "ufc.hpp"

int main(int, char**) {
    std::cout << "Booting up " << Config::Name << " " << Config::Version << ";" << std::endl;
    std::cout << Config::License << std::endl << std::endl;

    // init("app.lua");
    // close();
    // printf( "Press enter to exit..." );
    // getchar();

    UFC* ufc = new UFC(WINDOW_WIDTH, WINDOW_HEIGHT, 60, false, TITLE);
    ufc->Run();
}
