cmake_minimum_required(VERSION 3.10)
project(minimax_connect4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/common_tools
        ${PROJECT_SOURCE_DIR}/curses_wrapper
        ${PROJECT_SOURCE_DIR}/main_game
        ${PROJECT_SOURCE_DIR}/minimax_algorithm
)

add_executable(minimax_connect4
        main.cpp
        common_tools/common_tools.cpp
        common_tools/common_tools.hpp
        minimax_algorithm/minimax_algorithm.cpp
        minimax_algorithm/minimax_algorithm.hpp
        curses_wrapper/curses_wrapper.cpp
        curses_wrapper/curses_wrapper.hpp
        main_game/connect4_curses.cpp
        main_game/connect4_curses.hpp)
target_link_libraries(minimax_connect4 -lncurses)
