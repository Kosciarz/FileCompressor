#include "FileCompressor.h"

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

FileCompressor::FileCompressor(std::filesystem::path file_path)
    : ICompressor(),
      m_FilePath(std::move(file_path))
{
}

void FileCompressor::Run()
{
    const std::string data = ReadDataFromFile();
    std::map<std::string, int> dict;
    int dictSize = 256;

    for (int i = 0; i < dictSize; i++)
        dict[{static_cast<char>(i)}] = i;

    std::vector<int> codes;
    std::string sequence;

    for (const char& character : data)
    {
        if (const std::string charsToAdd = sequence + character; dict.contains(charsToAdd))
            sequence = charsToAdd;
        else
        {
            codes.push_back(dict[sequence]);
            dict[charsToAdd] = dictSize++;
            sequence = character;
        }
    }

    if (!sequence.empty())
        codes.push_back(dict[sequence]);

    WriteDataToFile(codes);
}

std::string FileCompressor::ReadDataFromFile() const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::in);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << "\n";
        throw std::runtime_error("Error: could not open the file!");
    }

    std::string data;
    std::string fileLine;

    while (std::getline(file, fileLine))
        data += fileLine + "\n";

    return data;
}

void FileCompressor::WriteDataToFile(const std::vector<int>& codes) const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::out | std::fstream::trunc);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << "\n";
        throw std::runtime_error("Error: could not open the file!");
    }

    for (const auto& code : codes)
        file << code << "\n";

    file.close();
}
