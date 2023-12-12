#include <iostream>
#include "config.hpp"

int main(int, char**) {
    std::cout << "Booting up " << Config::Name << " " << Config::Version << ";" << std::endl;
    std::cout << Config::License << std::endl << std::endl;
}
