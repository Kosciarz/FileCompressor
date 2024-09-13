#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "FileCompressor.h"

FileCompressor::FileCompressor(std::string filePath) : ICompressor(), m_FilePath(std::move(filePath))
{
}

void FileCompressor::Process()
{
    const std::string data = ReadDataFromFile();
    std::map<std::string, int> dict;
    int dict_size = 256;
    for (int i = 0; i < dict_size; i++)
    {
        dict[{static_cast<char>(i)}] = i;
    }
    std::vector<int> codes;
    std::string sequence;
    for (const char& character : data)
    {
        if (const std::string charsToAdd = sequence + character; dict.contains(charsToAdd))
        {
            sequence = charsToAdd;
        }
        else
        {
            codes.push_back(dict[sequence]);
            dict[charsToAdd] = dict_size++;
            sequence = character;
        }
    }
    if (!sequence.empty())
    {
        codes.push_back(dict[sequence]);
    }
    WriteDataToFile(codes);
}

std::string FileCompressor::ReadDataFromFile() const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::in);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    std::string data, file_line;
    while (std::getline(file, file_line))
    {
        data += file_line + "\n";
    }
    return data;
}

void FileCompressor::WriteDataToFile(const std::vector<int>& codes) const
{
    std::fstream file;
    file.open(m_FilePath, std::fstream::out | std::fstream::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << "\n";
        exit(EXIT_FAILURE);
    }
    for (const auto& code : codes)
    {
        file << code << "\n";
    }
    file.close();
}
