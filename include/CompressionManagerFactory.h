#pragma once

#include <memory>

#include "ICompressor.h"


class CompressionManagerFactory {
public:
    static std::unique_ptr<ICompressor> CreateCompressionManager(const std::string &operation,
                                                                 const std::string &filePath);
};
