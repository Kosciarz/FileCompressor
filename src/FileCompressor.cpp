#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "FileCompressor.h"

FileCompressor::FileCompressor(std::string file_path) : ICompressor(), m_file_path(std::move(file_path)) {
}

void FileCompressor::Process() {
    const std::string data = ReadDataFromFile();
    std::map<std::string, int> dict;
    int dict_size = 256;
    for (int i = 0; i < dict_size; i++) {
        dict[{static_cast<char>(i)}] = i;
    }
    std::vector<int> codes;
    std::string sequence;
    for (const char character: data) {
        if (const std::string chars_to_add = sequence + character; dict.contains(chars_to_add)) {
            sequence = chars_to_add;
        } else {
            codes.push_back(dict[sequence]);
            dict[chars_to_add] = dict_size++;
            sequence = character;
        }
    }
    if (!sequence.empty()) {
        codes.push_back(dict[sequence]);
    }
    WriteDataToFile(codes);
}

std::string FileCompressor::ReadDataFromFile() const {
    std::fstream file;
    file.open(m_file_path, std::fstream::in);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    std::string data, file_line;
    while (std::getline(file, file_line)) {
        data += file_line + "\n";
    }
    return data;
}

void FileCompressor::WriteDataToFile(const std::vector<int> &codes) const {
    std::fstream file;
    file.open(m_file_path, std::fstream::out | std::fstream::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    for (const auto &code: codes) {
        file << code << "\n";
    }
}
