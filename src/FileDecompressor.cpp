#include "FileDecompressor.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>

FileDecompressor::FileDecompressor(std::filesystem::path filePath)
    : ICompressor(),
      m_FilePath(std::move(filePath))
{
}

void FileDecompressor::Run()
{
    const std::vector<int> codes = ReadCodesFromFile();
    std::map<int, std::string> dict;
    int dict_size = 256;

    for (int i{}; i < dict_size; i++)
        dict[i] = static_cast<char>(i);

    std::string decompressedData, pes;

    for (const int& code : codes)
    {
        if (dict.contains(code))
        {
            decompressedData += dict[code];
            pes += dict[code][0];
            dict[dict_size++] = pes;
        }
        else
        {
            const std::string value = pes + dict[code][0];
            dict[dict_size++] = value;
            decompressedData += value;
        }
    }

    WriteDataToFile(decompressedData);
}

std::vector<int> FileDecompressor::ReadCodesFromFile() const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::in);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << '\n';
        throw std::runtime_error("Error opening the file!");
    }

    std::vector<int> codes;
    std::string fileLine;

    while (std::getline(file, fileLine))
        codes.push_back(std::stoi(fileLine));

    file.close();
    return codes;
}

void FileDecompressor::WriteDataToFile(const std::string& data) const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::trunc | std::fstream::out);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << '\n';
        throw std::runtime_error("Error opening the file!");
    }

    file << data;
    file.close();
}
