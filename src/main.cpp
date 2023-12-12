#include <iostream>
#include "config.hpp"

int main(int, char**) {
    std::cout << "Booting " << Config::Name << " v" << Config::Version << " up;" << std::endl;
    std::cout << std::endl << Config::License << std::endl << std::endl;
}
