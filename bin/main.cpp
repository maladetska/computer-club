#include <filesystem>
#include <iostream>

#include "lib/computer_club.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide input file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::filesystem::path       path = argv[1];
    computer_club::ComputerClub club(path);

    club.LaunchApp();

    return EXIT_SUCCESS;
}
