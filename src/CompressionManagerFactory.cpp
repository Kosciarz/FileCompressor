#include <iostream>
#include <string>

#include "CompressionManagerFactory.h"
#include "ICompressor.h"
#include "FileCompressor.h"
#include "FileDecompressor.h"

std::unique_ptr<ICompressor> CompressionManagerFactory::CreateCompressionManager(const std::string& operation,
    const std::string& filePath)
{
    if (operation == "c")
    {
        return std::make_unique<FileCompressor>(filePath);
    }
    if (operation == "d")
    {
        return std::make_unique<FileDecompressor>(filePath);
    }
    std::cerr << "Invalid operation!" << "\n";
    exit(EXIT_FAILURE);
}
