cmake_minimum_required(VERSION 3.20)
project(FileCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)


set(SOURCES
        src/Main.cpp
        src/FileCompressor.cpp
        src/FileDecompressor.cpp
        src/CompressionManager.cpp
        src/ICompressor.cpp
        src/CompressionManagerFactory.cpp
        src/ZIPCompressor.cpp
        src/RARCompressor.cpp
)

add_executable(FileCompressor ${SOURCES} ${HEADER_FILES})
target_include_directories(FileCompressor PRIVATE ${CMAKE_SOURCE_DIR}/include)
