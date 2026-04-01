cmake_minimum_required(VERSION 3.16)
project(ShogiAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(src)

add_executable(ShogiAI
    src/main.cpp
    src/position.cpp
    src/position.h
    src/move.cpp
    src/move.h
    src/search.cpp
    src/search.h
    src/eval.cpp
    src/eval.h
    src/learning.cpp
    src/learning.h
    src/io.cpp
    src/io.h
)
