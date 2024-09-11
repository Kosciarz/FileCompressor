#pragma once

#include "ICompressor.h"
#include <map>
#include <string>
#include <vector>


class FileCompressor final : public ICompressor {
private:
    std::string m_file_path;

public:
    explicit FileCompressor(std::string file_path);

    void Process() override;

private:
    [[nodiscard]] std::string ReadDataFromFile() const;

    void WriteDataToFile(const std::vector<int> &codes) const;
};
