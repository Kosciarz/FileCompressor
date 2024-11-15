#pragma once

#include "ICompressor.h"

#include <filesystem>
#include <string>
#include <vector>

class FileDecompressor final : public ICompressor
{
public:
  FileDecompressor(std::filesystem::path filePath);
  
  void Run() override;

private:
  [[nodiscard]] std::vector<int> ReadCodesFromFile() const;

  void WriteDataToFile(const std::string& data) const;

  std::filesystem::path m_FilePath;
};
