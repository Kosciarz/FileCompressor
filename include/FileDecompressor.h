#pragma once

#include <vector>
#include <string>

#include "ICompressor.h"


class Decompressor final : public ICompressor {
private:
    std::string m_fileName;
    int m_dictSize = 256;
    std::map<int, std::string> m_dict;

public:
    explicit Decompressor(std::string fileName);

    void Process() override;

private:
    [[nodiscard]] std::vector<int> ReadCodesFromFile() const;

    void WriteDataToFile(const std::string &data) const;
};
