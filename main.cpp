#include <zconf.h>
#include "curses_wrapper/curses_wrapper.hpp"
#include "main_game/connect4_curses.hpp"

int main() {
    curses_wrapper c;
    std::vector<std::vector<char>> vec(6,std::vector<char>(6,'X')) ;
    c.middle_print(std::to_string(vec[1][0]));
    sleep(4);
    return 0;
}