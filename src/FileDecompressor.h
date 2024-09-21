#pragma once

#include <vector>
#include <string>
#include <map>

#include "ICompressor.h"

class FileDecompressor final : public ICompressor
{
public:
    explicit FileDecompressor(std::string file_path);

    void Process() override;

private:
    [[nodiscard]] std::vector<int> ReadCodesFromFile() const;

    void WriteDataToFile(const std::string& data) const;

    std::string file_path_;
};
