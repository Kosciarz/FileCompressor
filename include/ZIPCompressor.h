#pragma once

#include <string>

#include "ICompressor.h"


class ZIPCompressor final : public ICompressor
{
public:
    explicit ZIPCompressor(std::string file_path);

    void Process() override;

private:
    std::string file_path_;
};
