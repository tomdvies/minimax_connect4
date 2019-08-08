//
// Created by mdavies4 on 09/07/2019.
//

#ifndef MINIMAX_CURSES_WRAPPER_HPP
#define MINIMAX_CURSES_WRAPPER_HPP

#endif //MINIMAX_CURSES_WRAPPER_HPP


#include <iostream>
#include <string>
#include <curses.h>
#include <vector>

class curses_wrapper {
private:
    int initalise();
    std::vector<int> get_string_coords(std::string string);
public:
    curses_wrapper(){
        this->initalise();}
    void middle_print(std::string string);
    void clear_screen();
    void close_screen();
    std::string get_string(std::string message);
    int get_int(std::string message);

};



