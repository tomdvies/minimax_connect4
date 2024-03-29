//
// Created by tom on 08/08/19.
//

#include <string>
#include <vector>
#include "connect4_curses.hpp"
#include "../curses_wrapper/curses_wrapper.hpp"
#include <chrono>
#include <thread>
#include <fstream>

#include <iterator>
#include "../minimax_algorithm/minimax_algorithm.hpp"

std::string board(std::vector<std::vector<char>>);
void main_game();
std::vector<std::vector<char>> print_move(std::vector<std::vector<char>> old_board,char team,int player,char enemy);
int get_move(std::vector<std::vector<char>> board_vector,int player);
int checkwin(std::vector<std::vector<char>> board,char player);
std::vector<std::vector<char>> make_move(std::vector<std::vector<char>> board,int move,char player);
void save_board(std::vector<std::vector<char>> board);
std::vector<std::vector<char>> load_board(std::string file);
void dump_message_1(std::string message);
void test_game();

curses_wrapper c;

void test_game(){
    std::vector<std::vector<char>> easy_short ={std::vector<char> {'O','X','O','X',' ',' '},std::vector<char> {'X','O','X','O',' ','X'},std::vector<char> {'O','X','O','X','O','X'},std::vector<char> {'O','X','O','X','O','X'},std::vector<char> {'X','O','X','O','X','O'},std::vector<char> {'X','O','X','O','X','O'}};
    std::vector<std::vector<char>> easy_long ={std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ','O','O','O',' ',' '},std::vector<char> {' ','X','X','X',' ',' '}};
}

void main_game(){

    int player = 2;
    int won =-1;
    char mark;
    char mark_e;
    c.clear_screen();
//    std::vector<std::vector<char>> board_vector(6,std::vector<char>(6,' ')) ;
    std::vector<std::vector<char>> board_vector ={std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {' ',' ',' ',' ',' ',' '},std::vector<char> {'O','X','O','X','O','X'},std::vector<char> {'X','O','X','O','X','O'},std::vector<char> {'X','O','X','O','X','O'}};
//    std::vector<std::vector<char>> board_vector ={std::vector<char> {'O','X','O','X',' ',' '},std::vector<char> {'X','O','X','O',' ','X'},std::vector<char> {'O','X','O','X','O','X'},std::vector<char> {'O','X','O','X','O','X'},std::vector<char> {'X','O','X','O','O','O'},std::vector<char> {'X','O','X','O','X','O'}};

    while(won ==-1){
        player=(player==2)?1:2;
        mark=(player == 1) ? 'X' : 'O';
        mark_e=(player==1) ? 'O' : 'X';
        board_vector = print_move(board_vector,mark,player,mark_e);
        won = checkwin(board_vector,mark);
        c.get_int("");
    }
    c.clear_screen();
    if (won == 0){
        c.get_int("Game draw.\n"+board(board_vector)+"\n\nPress any key to leave.");
        c.get_int("");
    }
    else c.get_int("Player "+std::to_string(player)+" ("+mark+") won.\n"+board(board_vector)+"\n\nPress any key to leave.");
    c.close_screen();
}


//std::vector<std::vector<char>> make_move(std::vector<std::vector<char>> board,int move,char player){
//    std::vector<std::vector<char>> new_board = board;
//    for (int i =0; i<board.size();i++){
//        if (board[i][move]!=' '){
//            return new_board;
//        }
//        new_board=board;
//        new_board[i][move]=player;
//    }
//    return new_board;
//}


int checkwin(std::vector<std::vector<char>> board,char player){
    int board_height = board.size();
    int board_width = board[0].size();
    for(int y = 0; board_height > y; y++){
        for (int x = 0;board_width-3 > x; x=x+1){
            if (board[y][x] == player and board[y][x+1] == player and board[y][x+2] == player and board[y][x+3] == player)
                return 1;
        }
    }
    for(int y = 0; board_height-3 > y; y++){
        for (int x = 0;board_width > x; x=x+1){
            if (board[y][x] == player and board[y+1][x] == player and board[y+2][x] == player and board[y+3][x] == player)
                return 1;
        }
    }
    for(int y = 0; board_height-3 > y; y++){
        for (int x = 0;board_width-3 > x; x=x+1){
            if (board[y][x] == player and board[y+1][x+1] == player and board[y+2][x+2] == player and board[y+3][x+3] == player)
                return 1;
        }
    }
    for(int y = 3; board_height  > y; y++){
        for (int x = 0;board_width > x; x=x+1){
            if (board[y][x] == player and board[y-1][x+1] == player and board[y-2][x+2] == player and board[y-3][x+3] == player)
                return 1;
        }
    }
    for(int y=0;board_height>y;y++){
        for(int x=0;board_width>x;x++){
            if (board[x][y] ==' ') return -1;
        }
    }
    return 0;
}


int get_move(std::vector<std::vector<char>> board_vector,int player){
    c.clear_screen();
    int move = c.get_int("Player 1 (X) vs Player 2 (O)\n"+board(board_vector)+"\n\nPlayer "+std::to_string(player)+" please enter your choice:");
    return move;
}

void dump_message_1(std::string message){
    std::ofstream out("output.txt");
    out << message;
    out.close();
}

void save_board(std::vector<std::vector<char>> board){
    std::string out;
    out = "std::vector<std::vector<char>> board ={";
    for (int i =0;board.size() > i;i++ ){
        out=out+"std::vector<char> {";
        for(int x=0; board[0].size() > x; x++){
            if (x==board[0].size()-1)out=out+"'"+board[i][x]+"'}";
            else out= out+"'"+board[i][x]+"'"",";
        }
        out+=",";
    }
    out+="}";
    dump_message_1(out);
}

std::vector<std::vector<char>> print_move(std::vector<std::vector<char>> old_board,char team,int player,char enemy){
    c.clear_screen();
    int move;
//    if (team == 'O')
    move = choice_minimax(checkwin,old_board,team,enemy);
//    else move = get_move(old_board,player) -1;
    if (move ==-1)
    save_board(old_board);

    while (move > old_board[0].size() or 0 > move){
        c.clear_screen();
//        c.get_int(std::string(1,(static_cast<int>(old_board[0].size()))));
        c.get_string("Error This is an invalid move please press enter to try again."+std::to_string(move));
        move = get_move(old_board,player) -1;
        //move =4;
    }
    while (old_board[0][move] != ' '){
        c.clear_screen();
        c.get_string("Error This is an invalid move please press enter to try again."+std::to_string(move));
        move = get_move(old_board,player) -1;
    }
    std::vector<std::vector<char>> new_board = old_board;
    for (int i =0; i<old_board.size();i++){
        if (old_board[i][move]!=' '){
            return new_board;
        }
        new_board=old_board;
        new_board[i][move]=team;
        c.clear_screen();
        c.middle_print("Player 1 (X) vs Player 2 (O)\n"+board(new_board)+"\n\nPlacing piece.");
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}

std::string board(std::vector<std::vector<char>> board_vector){
    std::string board_string ="";
    //board_string = board_string+ "\n\nConnect 4\n\n";

    board_string += "\n\n      ";
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
    board_string+="\n";
    return board_string;
//    if (aiplayer==1){board_string = board_string+"AI Player (X) - Player 1 (O)" + "\n\n";}
//    else board_string = board_string+"Player 1 (X)  -  AI Player (O)" + "\n\n";

}