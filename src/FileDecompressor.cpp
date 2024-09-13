#include <iostream>
#include <fstream>
#include <vector>

#include "FileDecompressor.h"

FileDecompressor::FileDecompressor(std::string filePath) : ICompressor(), m_FilePath(std::move(filePath))
{
}

void FileDecompressor::Process()
{
    const std::vector<int> codes = ReadCodesFromFile();
    std::map<int, std::string> dict;
    int dictSize = 256;
    for (int i = 0; i < dictSize; i++)
    {
        dict[i] = {static_cast<char>(i)};
    }
    std::string decompressedData, pes;

    for (const int& code : codes)
    {
        if (dict.contains(code))
        {
            decompressedData += dict[code];
            pes += dict[code][0];
            dict[dictSize++] = pes;
        }
        else
        {
            const std::string v = pes + dict[code][0];
            dict[dictSize++] = v;
            decompressedData += v;
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
        std::cerr << "Error opening the file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<int> codes;
    std::string file_line;
    while (std::getline(file, file_line))
    {
        codes.push_back(std::stoi(file_line));
    }
    file.close();
    return codes;
}

void FileDecompressor::WriteDataToFile(const std::string& data) const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::trunc | std::fstream::out);
    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    file << data;
    file.close();
}
