#pragma once

#include "ICompressor.h"

#include <memory>
#include <string>

class CompressionManagerFactory
{
public:
    static std::unique_ptr<ICompressor> CreateCompressionManager(
        const std::string& operation,
        const std::string& file_path
    );
};
