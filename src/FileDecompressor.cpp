#include <iostream>
#include <fstream>
#include <vector>

#include "FileDecompressor.h"

FileDecompressor::FileDecompressor(std::string file_path) : ICompressor(), file_path_(std::move(file_path))
{
}

void FileDecompressor::Process()
{
    const std::vector<int> codes = ReadCodesFromFile();
    std::map<int, std::string> dict;
    int dict_size = 256;
    for (int i = 0; i < dict_size; i++)
    {
        dict[i] = {static_cast<char>(i)};
    }
    std::string decompressed_data, pes;

    for (const int& code : codes)
    {
        if (dict.contains(code))
        {
            decompressed_data += dict[code];
            pes += dict[code][0];
            dict[dict_size++] = pes;
        }
        else
        {
            const std::string v = pes + dict[code][0];
            dict[dict_size++] = v;
            decompressed_data += v;
        }
    }
    WriteDataToFile(decompressed_data);
}

std::vector<int> FileDecompressor::ReadCodesFromFile() const
{
    std::fstream file;
    file.open(file_path_, std::fstream::in);
    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << '\n';
		throw std::exception("Error opening the file!");
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
    file.open(file_path_, std::fstream::trunc | std::fstream::out);
    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << '\n';
		throw std::exception("Error opening the file!");
    }
    file << data;
    file.close();
}
