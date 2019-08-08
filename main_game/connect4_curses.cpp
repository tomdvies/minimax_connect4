//
// Created by tom on 08/08/19.
//

#include <string>
#include <vector>
#include "connect4_curses.hpp"
#include "../curses_wrapper/curses_wrapper.hpp"
#include <chrono>
#include <thread>


std::string board(std::vector<std::vector<char>>);
void main_game();
std::vector<std::vector<char>> print_move(std::vector<std::vector<char>> old_board,char team);
int get_move(std::vector<std::vector<char>> old_board);
int checkwin(std::vector<std::vector<char>> board,char player);

curses_wrapper c;



void main_game(){
    int player = 1;
    int won =-1;
    char mark;
    std::vector<std::vector<char>> board_vector(6,std::vector<char>(6,' ')) ;
    while(won ==-1){
        player=(player==2)?1:2;
        mark=(player == 1) ? 'X' : 'O';
        board_vector = print_move(board_vector,mark);
        won = checkwin(board_vector,mark);
    }
}
int checkwin(std::vector<std::vector<char>> board,char player){
    return -1;

}


int get_move(std::vector<std::vector<char>> board_vector){
    c.clear_screen();
    int move = c.get_int(board(board_vector)+"\nPlease enter your choice:");
    return move;
}

std::vector<std::vector<char>> print_move(std::vector<std::vector<char>> old_board,char team){
    c.clear_screen();

    int move = get_move(old_board) -1;
    while (move > old_board[0].size() or 0 > move){
        c.clear_screen();
//        c.get_int(std::string(1,(static_cast<int>(old_board[0].size()))));
        c.get_string("Error This is an invalid move please press enter to try again.");
        move = get_move(old_board) -1;
        //move =4;
    }
    while (old_board[0][move] != ' '){
        c.clear_screen();
        c.get_string("Error This is an invalid move please press enter to try again.");
        move = get_move(old_board) -1;
    }
    std::vector<std::vector<char>> new_board = old_board;
    for (int i =0; i<old_board.size();i++){
        if (old_board[i][move]!=' '){
            return new_board;
        }
        new_board=old_board;
        new_board[i][move]=team;
        c.clear_screen();
        c.middle_print(board(new_board)+"\nPlacing piece.");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::string board(std::vector<std::vector<char>> board_vector){
    std::string board_string ="";
    board_string = board_string+ "\n\nConnect 4\n\n";
    board_string += "      ";
    for (int i =0;i<board_vector[0].size();i++){
        board_string += std::to_string(i+1);
        board_string += "     ";
    }
    for (int i =0;i<board_vector.size();i++){
        if (i==0){
            board_string+="\n____";
            for(int f=0;f<(board_vector[i].size()-1);f++){
                board_string+="______";
            }
            board_string+="___";
        }
        if (i==0){
            board_string+="\n|   ";
            for(int f=0;f<(board_vector[i].size()-1);f++){
                board_string+="  |   ";
            }
            board_string+="  |";
        }
        board_string=board_string+"\n|  ";

        for (int x =0; x < board_vector[0].size(); x++){
//            board_string+="|  ";
            board_string=board_string+board_vector[i][x];
            if (x+1!=board_vector[i].size())
            board_string+="  |  ";
        }
        board_string+="  |\n|___";
        for(int f=0;f<(board_vector[i].size()-1);f++){
            board_string+="__|___";
        }
        board_string+="__|";
        if (i+1!=board_vector.size()){
        board_string+="\n|   ";
        for(int f=0;f<(board_vector[i].size()-1);f++){
            board_string+="  |   ";
        }
        board_string+="  |";
        }

    }
    return board_string;
//    if (aiplayer==1){board_string = board_string+"AI Player (X) - Player 1 (O)" + "\n\n";}
//    else board_string = board_string+"Player 1 (X)  -  AI Player (O)" + "\n\n";

}