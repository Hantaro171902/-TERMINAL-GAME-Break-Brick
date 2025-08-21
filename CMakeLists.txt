cmake_minimum_required(VERSION 3.10)

# Project name and version
project(BreakBrick VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and header files
set(SOURCES
    src/main.cpp
    src/ultils.cpp
    src/board.cpp
    src/game.cpp
    src/ball.cpp
    src/paddle.cpp
    src/color.cpp
)

set(HEADERS
    src/headers/game.hpp
    src/headers/ultils.hpp
    src/headers/board.hpp
    src/headers/paddle.hpp
    src/headers/ball.hpp
    src/headers/color.hpp
)

# Exe
add_executable(breakBrick ${SOURCES} ${HEADERS})

target_include_directories(breakBrick PRIVATE src/headers)

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
