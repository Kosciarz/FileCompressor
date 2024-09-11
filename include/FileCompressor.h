#pragma once

#include "ICompressor.h"
#include <map>
#include <string>
#include <vector>


class Compressor final : public ICompressor {
private:
    std::string m_fileName;
    int m_dictSize = 256;
    std::map<std::string, int> m_dict;

public:
    explicit Compressor(std::string fileName);

    void Process() override;

private:
    [[nodiscard]] std::string ReadDataFromFile() const;

    void WriteDataToFile(const std::vector<int> &codes) const;
};
