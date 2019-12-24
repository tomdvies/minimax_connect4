//
// Created by tom on 08/08/19.
//

#ifndef MINIMAX_CONNECT4_CONNECT4_CURSES_HPP
#define MINIMAX_CONNECT4_CONNECT4_CURSES_HPP
#include "board.h"
enum GameResult { WIN=1, ONGOING=-1, DRAW=0};
GameResult checkwin(Board board,char player);
void main_game();
#endif //MINIMAX_CONNECT4_CONNECT4_CURSES_HPP

