#include <iostream>
#include <memory>
#include <algorithm>

#include "ICompressor.h"
#include "CompressionManager.h"
#include "CompressionManagerFactory.h"

CompressionManager::CompressionManager(std::unique_ptr<ICompressor> operation) : m_operation(std::move(operation)) {
}

void CompressionManager::StartProgram() {
    std::string operation, file_path;
    std::cout << "Chose operation: " << "\n";
    std::cout << "\t(C)ompress file" << "\n";
    std::cout << "\t(D)ecompress file" << "\n";
    std::cin >> operation;
    std::cout << "Path to file: " << "\n";
    std::cin >> file_path;

    std::ranges::transform(operation, operation.begin(), ::tolower);

    auto base = CompressionManagerFactory::CreateCompressionManager(operation, file_path);
    const auto manager = CompressionManager(std::move(base));
    manager.m_operation->Process();
}
