#pragma once

#include "ICompressor.h"

#include <string>
#include <vector>
#include <filesystem>

class FileCompressor final : public ICompressor
{
public:
    FileCompressor(std::filesystem::path filePath);

    void Run() override;

private:
    [[nodiscard]] std::string ReadDataFromFile() const;

    void WriteDataToFile(const std::vector<int>& codes) const;

    std::filesystem::path m_FilePath;
};
