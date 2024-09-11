#pragma once

#include <vector>
#include <string>
#include <map>

#include "ICompressor.h"

class FileDecompressor final : public ICompressor {
private:
    std::string m_file_path;

public:
    explicit FileDecompressor(std::string file_name);

    void Process() override;

private:
    [[nodiscard]] std::vector<int> ReadCodesFromFile() const;

    void WriteDataToFile(const std::string &data) const;
};
