#pragma once

#include <string>

#include "ICompressor.h"

class RARCompressor final : public ICompressor
{
public:
    explicit RARCompressor(std::string file_path);

    void Process() override;

private:
    std::string file_path_;
};
