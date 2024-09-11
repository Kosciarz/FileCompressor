#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "Decompressor.h"

Decompressor::Decompressor(std::string fileName) : ICompressor(), m_fileName(std::move(fileName)) {
}

void Decompressor::Process() {
    const std::vector<int> codes = ReadCodesFromFile();
    for (int i = 0; i < m_dictSize; i++) {
        m_dict[i] = {static_cast<char>(i)};
    }
    std::string decompressedData, pes;

    for (const int &code: codes) {
        if (m_dict.contains(code)) {
            decompressedData += m_dict[code];
            pes += m_dict[code][0];
            m_dict[m_dictSize++] = pes;
        } else {
            const std::string v = pes + m_dict[code][0];
            m_dict[m_dictSize++] = v;
            decompressedData += v;
        }
    }
    WriteDataToFile(decompressedData);
}

void Decompressor::WriteDataToFile(const std::string &data) const {
    std::fstream file;
    file.open(m_fileName, std::fstream::trunc | std::fstream::out);
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    file << data;
    file.close();
}
