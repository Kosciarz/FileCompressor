#pragma once

#include "ICompressor.h"

#include <string>

class ZIPCompressor final : public ICompressor
{
public:
    explicit ZIPCompressor(std::string file_path);

    void Process() override;

private:
    std::string file_path_;
};
