#include "ICompressor.h"
#include "CompressionManager.h"
#include "CompressionManagerFactory.h"

#include <iostream>
#include <memory>
#include <algorithm>

CompressionManager::CompressionManager(std::unique_ptr<ICompressor> operation)
    : m_operation(std::move(operation))
{
}

void CompressionManager::Run()
{
    std::cout << "Welcome to File Compressor / Decompressor!\n";
    int operation{};

    do
    {
        std::cout << "\nChose operation:\n";
        std::cout << "1. Compress file\n";
        std::cout << "2. Decompress file\n";
        std::cout << "3. Exit\n";
        std::cin >> operation;

        if (std::cin.fail() || operation < 1 || operation > 3)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nEnter a valid operation! Please try again\n";
            continue;
        }

        if (operation == 3)
            return;

        std::cout << "Path to file: " << "\n";
        std::string file_path;
        std::cin >> file_path;

        auto base = CompressionManagerFactory::CreateCompressionManager(operation, file_path);
        const auto manager = CompressionManager(std::move(base));
        manager.m_operation->Process();
    } while (true);
}
