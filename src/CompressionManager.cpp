#include "FileCompressor.h"

#include <Compressor.h>
#include <Decompressor.h>
#include <iostream>
#include <memory>

std::unique_ptr<Base> FileCompressorFactory(const std::string &operation, std::string &fileName);

CompressionManager::CompressionManager(std::unique_ptr<Base> base) : m_Base()

void CompressionManager::StartProgram(const int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "" << "\n";
        exit(EXIT_FAILURE);
    }
    std::string operation = argv[1];
    std::string fileName = argv[2];

    auto base = FileCompressorFactory(operation, fileName);
    CompressionManager file_compressor(std::move(base));
}


static std::unique_ptr<Base> FileCompressorFactory(
    const std::string &operation,
    const std::string &fileName) {
    if (operation == "-c") {
        return std::make_unique<Compressor>(fileName);
    }
    if (operation == "-d") {
        return std::make_unique<Decompressor>(fileName);
    }
    std::cerr << "Invalid operation!" << "\n";
    exit(EXIT_FAILURE);
}
