#include <iostream>

#include "FileCompressor.h"

int main(const int argc, char *argv[]) {
    FileCompressor::StartProgram(argc, argv);
    std::cout << "Program finished successfully." << std::endl;
    std::cin.get();
}
