#include <iostream>
#include <string>

#include "CompressionManagerFactory.h"
#include "ICompressor.h"
#include "FileCompressor.h"
#include "FileDecompressor.h"

std::unique_ptr<ICompressor> CompressionManagerFactory::CreateCompressionManager(
	const std::string& operation,
    const std::string& file_path
    )
{
    if (operation == "c")
	    return std::make_unique<FileCompressor>(file_path);

	if (operation == "d")
		return std::make_unique<FileDecompressor>(file_path);

    std::cerr << "Invalid operation!" << "\n";
	throw std::runtime_error("Invalid operation");
}
