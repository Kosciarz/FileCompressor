#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "Compressor.h"


Compressor::Compressor(std::string fileName) : ICompressor(), m_fileName(std::move(fileName)) {
}

void Compressor::Process() {
    const std::string data = ReadDataFromFile();
    for (int i = 0; i < m_dictSize; i++) {
        m_dict[{static_cast<char>(i)}] = i;
    }
    std::vector<int> codes;
    std::string sequence;
    for (const char character: data) {
        if (const std::string charsToAdd = sequence + character; m_dict.contains(charsToAdd)) {
            sequence = charsToAdd;
        } else {
            codes.push_back(m_dict[sequence]);
            m_dict[charsToAdd] = m_dictSize++;
            sequence = character;
        }
    }
    if (!sequence.empty()) {
        codes.push_back(m_dict[sequence]);
    }
    WriteDataToFile(codes);
}

std::string Compressor::ReadDataFromFile() const {
    std::fstream file;
    file.open(m_fileName, std::fstream::in);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    std::string data, fileLine;
    while (std::getline(file, fileLine)) {
        data += fileLine;
    }
    return data;
}

void Compressor::WriteDataToFile(const std::vector<int> &codes) const {
    std::fstream file;
    file.open(m_fileName, std::fstream::out | std::fstream::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    for (const auto &code: codes) {
        file << code << " ";
    }
}
