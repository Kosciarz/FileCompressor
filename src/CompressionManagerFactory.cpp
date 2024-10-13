#include "CompressionManagerFactory.h"
#include <CompressionManager.h>
#include "ICompressor.h"
#include "FileCompressor.h"
#include "FileDecompressor.h"

#include <iostream>
#include <string>

std::unique_ptr<ICompressor> CompressionManagerFactory::CreateCompressionManager(
    const int operation,
    const std::string& file_path
)
{
    if (operation == 1)
        return std::make_unique<FileCompressor>(file_path);
    if (operation == 2)
        return std::make_unique<FileDecompressor>(file_path);
        
    std::cerr << "Invalid operation!" << "\n";
    throw std::runtime_error("Invalid operation");
}
