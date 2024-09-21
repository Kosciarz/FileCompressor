cmake_minimum_required(VERSION 3.20)
project(FileCompressor VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

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


foreach (SOURCE ${SOURCES})
    message(STATUS "Source file: ${SOURCE}")
endforeach ()

add_executable(FileCompressor ${SOURCES} ${HEADER_FILES})
target_include_directories(FileCompressor PRIVATE ${CMAKE_SOURCE_DIR}/include)
