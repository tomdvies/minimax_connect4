//
// Created by mdavies4 on 09/07/2019.
//

#include "curses_wrapper.hpp"
#include <curses.h>

#include <cmath>
#include <sstream>
#include <vector>
#include <string.h>
#include "../common_tools/common_tools.hpp"


int curses_wrapper::initalise() {
    initscr();
    cbreak();
    clear();
    refresh();
    return 0;
}


void curses_wrapper::close_screen() {
    clear();
    refresh();
    endwin();
}

std::vector<int> curses_wrapper::get_string_coords(std::string string) {
    std::vector<int> coord;
    coord.assign(2,0);




    int row,col;

    getmaxyx(stdscr,row,col);

    //  find center point of screen.
    coord[0] = col/2;
    coord[1] = row/2;

    int lines;
    lines = 1;
    std::stringstream main_string(string);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(main_string, segment, '\n'))
    {
        lines++;
        seglist.push_back(segment);
    }

    int longest = 0;

    for(int i=0;i<seglist.size();i++){
        if (seglist[i].length()>longest)
            longest = seglist[i].length();
    }
    int shift_col = llround((float)longest/2);
    coord[0] = coord[0]-shift_col;
    coord[1] = coord[1]-(lines/2);



//    printw(reinterpret_cast<const char *>( coord[1]));
    return coord;


}
void multilinemvprintw(std::string string, int x, int y){
    std::stringstream main_string(string);
    std::string segment;
    std::vector<std::string> seglist;
    int row,col;
    getmaxyx(stdscr,row,col);

    while(std::getline(main_string, segment, '\n'))
    {
        seglist.push_back(segment);
    }
    for(int i = 0;i<seglist.size();i++){
        mvprintw(y+i,(col-strlen(string_to_const_char_pointer(seglist[i])))/2,string_to_const_char_pointer(seglist[i]));
    }

}


void curses_wrapper::middle_print(std::string string) {
    std::string message = string;
    std::vector<int> coords = get_string_coords(message);
    multilinemvprintw(message, coords[0], coords[1]);
    refresh();
}

int curses_wrapper::get_int(std::string message) {
    std::vector<int> coords = get_string_coords(message);
    multilinemvprintw(message,coords[0],coords[1]);
    refresh();
    int number;
    char x  =getchar();
    number = x -'0';
    return number;
}

void curses_wrapper::clear_screen(){
    clear();
}

std::string curses_wrapper::get_string(std::string message) {
    std::vector<int> coords = get_string_coords(message);
    multilinemvprintw(message,coords[0],coords[1]);
    std::string reply =std::to_string(getch());
    refresh();
    return reply;
}