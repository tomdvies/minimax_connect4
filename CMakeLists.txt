cmake_minimum_required(VERSION 3.14)
project(minimax_connect4)

set(CMAKE_CXX_STANDARD 14)

add_executable(minimax_connect4 main.cpp common_tools/common_tools.cpp common_tools/common_tools.hpp minimax_algorithm/minimax_algorithm.cpp minimax_algorithm/minimax_algorithm.hpp curses_wrapper/curses_wrapper.cpp curses_wrapper/curses_wrapper.hpp main_game/connect4_curses.cpp main_game/connect4_curses.hpp)
target_link_libraries(minimax_connect4 -lncurses)
