#pragma once


#include <memory>

#include "Base.h"

class CompressionManager {
private:
    std::unique_ptr<Base> m_Base;

public:
    explicit CompressionManager(std::unique_ptr<Base> base);

    static void StartProgram(int argc, char *argv[]);
};
