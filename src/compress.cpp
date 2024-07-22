#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "compress.h"

static std::string fileName;

static std::fstream openFileToRead();
static std::fstream openFileToWrite();
static std::string loadDataToCompress(std::fstream file);
static std::vector<int> loadCodesToDecompress(std::fstream file);
static void compressFile(const std::string &data);
static void decompressFile(const std::vector<int> &codes);

void startProgram(int argc, char *argv[])
{
    std::string operation = static_cast<std::string>(argv[1]);
    fileName = static_cast<std::string>(argv[2]);
    std::fstream file = openFileToRead();

    if (operation == "-c")
        compressFile(loadDataToCompress(std::move(file)));
    else if (operation == "-d")
        decompressFile(loadCodesToDecompress(std::move(file)));
    else
        std::cerr << "Wrong operation choosen." << std::endl;
}

static void compressFile(const std::string &data)
{
    //  Nie zrobiłem sam - musiałem skorzystać z filmiku na yt.
    //  Ale prawie się udało i to ważne.
    //  Dużo się nauczyłem.
    //  Teraz jeszcze zrobić dekompresor.
    //  I jeszcze obsługę że podaje nazwę pliku jako
    //  argument przy kompilacji i wybieram czy chcę
    //  skompresować czy zdekompresować.

    static int dictSize = 256;
    std::map<std::string, int> dict;
    for (int i = 0; i < dictSize; i++)
        dict[{static_cast<char>(i)}] = i;

    std::vector<int> codes;
    std::string sequnce = "", charsToAdd;
    char character;
    for (int i = 0; i < data.length(); i++)
    {
        character = static_cast<char>(data[i]);
        charsToAdd = sequnce + character;
        if (dict.contains(charsToAdd))
            sequnce = charsToAdd;
        else
        {
            codes.push_back(dict[sequnce]);
            dict[charsToAdd] = dictSize++;
            sequnce = character;
        }
    }
    if (!sequnce.empty())
        codes.push_back(dict[sequnce]);

    std::fstream file = openFileToWrite();
    for (int const &code : codes)
        file << code << std::endl;
    file.close();
}

static void decompressFile(const std::vector<int> &codes)
{
    static int dictSize = 256;
    std::map<int, std::string> dict;
    for (int i = 0; i < dictSize; i++)
        dict[i] = {static_cast<char>(i)};

    std::string decompressedData;
    std::string pes;

    for (const int &code : codes)
    {
        if (dict.contains(code))
        {
            decompressedData += dict[code];
            pes += dict[code][0];
            dict[dictSize++] = pes;
        }
        else
        {
            std::string v = pes + dict[code][0];
            dict[dictSize++] = v;
            decompressedData += v;
        }
    }
    
    std::fstream file = openFileToWrite();
    file << decompressedData;
    file.close();
}

static std::fstream openFileToRead()
{
    std::fstream file;
    file.open(fileName, std::fstream::in);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << std::endl;
    }
    return file;
}

static std::fstream openFileToWrite()
{
    std::fstream file;
    file.open(fileName, std::fstream::out | std::fstream::trunc);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file!" << std::endl;
    }
    return file;
}

static std::string loadDataToCompress(std::fstream file)
{
    std::string data, fileLine;
    while (std::getline(file, fileLine))
        data += fileLine;
    return data;
}

static std::vector<int> loadCodesToDecompress(std::fstream file)
{
    std::vector<int> codes;
    std::string fileLine;
    while (std::getline(file, fileLine))
        codes.push_back(std::stoi(fileLine));
    return codes;
}