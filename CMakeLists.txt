cmake_minimum_required(VERSION 3.16)
project(ShogiAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ShogiAI
    src/main.cpp
    src/position.cpp
    src/move.cpp
    src/search.cpp
    src/eval.cpp
    src/learning.cpp
    src/io.cpp
)

if (MSVC)
    target_compile_options(ShogiAI PRIVATE /W4)
else()
    target_compile_options(ShogiAI PRIVATE -Wall -Wextra -Wpedantic)
endif()
