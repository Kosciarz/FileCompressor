#pragma once


#include <memory>

#include "ICompressor.h"

class CompressionManager {
private:
    std::unique_ptr<ICompressor> m_operation;

public:
    explicit CompressionManager(std::unique_ptr<ICompressor> operation);

    static void StartProgram();
};
