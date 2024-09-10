#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "compress.h"

class Compressor {
public:
    explicit Compressor(const std::string &fileName);
    void startProgram(int argc, char *argv[]);

private:
    int dictSize;
    std::string fileName;

    std::fstream openFileToRead() const;
    std::fstream openFileToWrite() const;
    std::string loadDataToCompress(std::fstream file);
    std::vector<int> loadCodesToDecompress(std::fstream file);
    void compressFile(const std::string &data);
    void decompressFile(const std::vector<int> &codes);
};

Compressor::Compressor(const std::string &fileName) : dictSize(256), fileName(fileName) {}
void Compressor::startProgram(int argc, char *argv[]) {
    const std::string operation = static_cast<std::string>(argv[1]);
    fileName = static_cast<std::string>(argv[2]);
    std::fstream file = openFileToRead();

    if (operation == "-c")
        compressFile(loadDataToCompress(std::move(file)));
    else if (operation == "-d")
        decompressFile(loadCodesToDecompress(std::move(file)));
    else
        std::cerr << "Wrong operation chosen." << std::endl;
}

void Compressor::compressFile(const std::string &data) {
    std::map<std::string, int> dict;
    for (int i = 0; i < dictSize; i++)
        dict[{static_cast<char>(i)}] = i;

    std::vector<int> codes;
    std::string sequence;
    for (int i = 0; i < data.length(); i++) {
        const char character = static_cast<char>(data[i]);
        const std::string charsToAdd = sequence + character;
        if (dict.contains(charsToAdd))
            sequence = charsToAdd;
        else {
            codes.push_back(dict[sequence]);
            dict[charsToAdd] = dictSize++;
            sequence = character;
        }
    }
    if (!sequence.empty())
        codes.push_back(dict[sequence]);

    std::fstream file = openFileToWrite();
    for (int const &code : codes)
        file << code << std::endl;
    file.close();
}

void Compressor::decompressFile(const std::vector<int> &codes) {
    int dictSize = 256;
    std::map<int, std::string> dict;
    for (int i = 0; i < dictSize; i++)
        dict[i] = {static_cast<char>(i)};

    std::string decompressedData;
    std::string pes;

    for (const int &code : codes) {
        if (dict.contains(code)) {
            decompressedData += dict[code];
            pes += dict[code][0];
            dict[dictSize++] = pes;
        } else {
            const std::string v = pes + dict[code][0];
            dict[dictSize++] = v;
            decompressedData += v;
        }
    }
    std::fstream file = openFileToWrite();
    file << decompressedData;
    file.close();
}

std::fstream Compressor::openFileToRead() const {
    std::fstream file;
    file.open(fileName, std::fstream::in);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << std::endl;
    }
    return file;
}

std::fstream Compressor::openFileToWrite() const {
    std::fstream file;
    file.open(fileName, std::fstream::out | std::fstream::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: could not open the file!" << std::endl;
    }
    return file;
}

std::string Compressor::loadDataToCompress(std::fstream file) {
    std::string data, fileLine;
    while (std::getline(file, fileLine)) {
        data += fileLine;
    }
    return data;
}

std::vector<int> Compressor::loadCodesToDecompress(std::fstream file) {
    std::vector<int> codes;
    std::string fileLine;
    while (std::getline(file, fileLine)) {
        codes.push_back(std::stoi(fileLine));
    }
    return codes;
}



