#include "ICompressor.h"
#include "CompressionManager.h"
#include "CompressionManagerFactory.h"

#include <iostream>
#include <memory>
#include <algorithm>

CompressionManager::CompressionManager(std::unique_ptr<ICompressor> operation) : operation_(std::move(operation))
{
}

void CompressionManager::Run()
{
    std::cout << "Chose operation: " << "\n";
    std::cout << "\t(C)ompress file" << "\n";
    std::cout << "\t(D)ecompress file" << "\n";
    std::string operation;
    std::cin >> operation;

    std::cout << "Path to file: " << "\n";
    std::string file_path;
    std::cin >> file_path;

    std::ranges::transform(operation, operation.begin(), ::tolower);

    auto base = CompressionManagerFactory::CreateCompressionManager(operation, file_path);
    const auto manager = CompressionManager(std::move(base));
    manager.operation_->Process();
}
