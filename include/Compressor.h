#pragma once

void startProgram(int argc, char* argv[]);

//write the class interface for the Compressor class here
class Compressor {
public:
    explicit Compressor(const std::string &fileName);
    void startProgram(int argc, char *argv[]);
private:
    int dictSize;
    std::string fileName;

    [[nodiscard]] std::fstream openFileToRead() const;
    [[nodiscard]] std::fstream openFileToWrite() const;
    std::string loadDataToCompress(std::fstream file);
    std::vector<int> loadCodesToDecompress(std::fstream file);
    void compressFile(const std::string &data);
    void decompressFile(const std::vector<int> &codes);
};