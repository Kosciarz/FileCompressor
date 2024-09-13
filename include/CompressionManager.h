#pragma once


#include <memory>

#include "ICompressor.h"

class CompressionManager
{
public:
    explicit CompressionManager(std::unique_ptr<ICompressor> operation);

    static void StartProgram();

private:
    std::unique_ptr<ICompressor> m_Operation;
};
