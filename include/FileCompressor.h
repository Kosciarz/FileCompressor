#pragma once

#include "ICompressor.h"
#include <string>
#include <vector>


class FileCompressor final : public ICompressor
{
public:
    explicit FileCompressor(std::string filePath);

    void Process() override;

private:
    [[nodiscard]] std::string ReadDataFromFile() const;

    void WriteDataToFile(const std::vector<int>& codes) const;

    std::string m_FilePath;
};
