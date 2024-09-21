#pragma once

#include "ICompressor.h"

#include <string>

class RARCompressor final : public ICompressor
{
public:
    explicit RARCompressor(std::string file_path);

    void Process() override;

private:
    std::string file_path_;
};
