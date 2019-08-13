#include <zconf.h>
#include <fstream>
#include "curses_wrapper/curses_wrapper.hpp"
#include "main_game/connect4_curses.hpp"

int main() {
    std::ofstream outfile;
    outfile.open("dumped_values.txt", std::ios_base::app);
    outfile << " ";
    main_game();
    return 0;
}