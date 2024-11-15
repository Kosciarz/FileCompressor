#include "Compressor.h"
#include "FileCompressor.h"
#include "FileDecompressor.h"
#include "ICompressor.h"

#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>

static void DisplayMenu();

std::unique_ptr<ICompressor> MakeCompressor(
    const int operation,
    std::filesystem::path filePath);

void RunCompressor()
{
  std::cout << "Welcome to File Compressor / Decompressor!" << '\n';
  int operation = 0;

  while (true)
  {
    DisplayMenu();

    std::cin >> operation;

    if (std::cin.fail() || operation < 1 || operation > 3)
    {
      std::cout << '\n'
                << "Wrong operation. Please try again." << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (operation == 3)
      break;

    std::cout << "Enter the file path: " << '\n';
    std::filesystem::path filePath;
    std::cin >> filePath;

    std::unique_ptr<ICompressor> compressor = MakeCompressor(operation, filePath);

    if (compressor != nullptr)
      compressor->Run();
    else
      std::cout << "Wrong operation. Please try again." << '\n';
  }
}

std::unique_ptr<ICompressor> MakeCompressor(
    const int operation,
    std::filesystem::path filePath)
{
  if (operation == 'c')
    return std::make_unique<FileCompressor>(filePath);
  if (operation == 'd')
    return std::make_unique<FileDecompressor>(filePath);

  return nullptr;
}

static void DisplayMenu()
{
  std::cout << '\n'
            << "Chose operation:" << '\n'
            << "1. Compress file" << '\n'
            << "2. Decompress file" << '\n'
            << "3. Exit" << '\n';
}