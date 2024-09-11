cmake_minimum_required(VERSION 3.20)
project(FileCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        src/Main.cpp
        src/FileCompressor.cpp
        src/FileDecompressor.cpp
        src/CompressionManager.cpp
        src/ICompressor.cpp
        src/CompressionManagerFactory.cpp
)

add_executable(FileCompressor ${SOURCES})
target_include_directories(FileCompressor PRIVATE ${CMAKE_SOURCE_DIR}/include)
