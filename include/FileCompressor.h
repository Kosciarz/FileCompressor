#pragma once

#include "ICompressor.h"

#include <string>
#include <vector>

class FileCompressor final : public ICompressor
{
public:
    explicit FileCompressor(std::string file_path);

    void Process() override;

private:
    [[nodiscard]] std::string ReadDataFromFile() const;

    void WriteDataToFile(const std::vector<int>& codes) const;

    std::string file_path_;
};
