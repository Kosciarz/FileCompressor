cmake_minimum_required(VERSION 3.20)
project(FileCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        src/Main.cpp
        src/Compressor.cpp
        src/Decompressor.cpp
        src/FileCompressor.cpp
        src/Base.cpp
        include/Base.h
)

add_executable(FileCompressor ${SOURCES})
target_include_directories(FileCompressor PRIVATE ${CMAKE_SOURCE_DIR}/include)
