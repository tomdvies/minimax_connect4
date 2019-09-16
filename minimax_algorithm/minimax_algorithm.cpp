//
// Created by tom on 24/07/19.
//

#include "minimax_algorithm.hpp"
#include <vector>
#include <fstream>

int function_calls = 0;

int minimax_evaluate(std::function<int(std::vector<std::vector<char>> square,char team)> checkwin, std::vector<std::vector<char>> square,char player, char team, char enemy,int move);
void dump_message(std::string message);
int minimax_evaluate(std::function<int(std::vector<std::vector<char>> square,char team)> checkwin, std::vector<std::vector<char>> square,char player, char team, char enemy,int move,int alpha,int beta);
std::string boardKey(std::vector<std::vector<char>> board);



std::vector<int> column_order(int width){
    std::vector<int> columnOrder(width,0);
    for(int i = 0; i < width; i++)
        columnOrder[i] = width/2 + (1-2*(i%2))*(i+1)/2;
    return columnOrder;
};


void dump_message(std::string message){
    std::ofstream outfile;
    outfile.open("dumped_values.txt", std::ios_base::app);
    outfile << message;
}

std::vector<std::vector<char>> make_move(std::vector<std::vector<char>> board,int move,char player){
    std::vector<std::vector<char>> new_board = board;
    for (int i =0; i<board.size();i++){
        if (board[i][move]!=' '){
            return new_board;
        }
        new_board=board;
        new_board[i][move]=player;
    }
    return new_board;
}

int choice_minimax(std::function<int(std::vector<std::vector<char>> square,char team)> checkwin, std::vector<std::vector<char>> square, char team, char enemy) {

    std::vector<std::vector<char>> new_square = square;
    std::vector<int> choices_values(square[0].size(),0);
    int choice =1;
//    choices_values.


    for (int i=0; square[0].size() > i; i=i+1){
        if (square[0][i] ==team or square[0][i] ==enemy){choices_values[i] = -100000000;continue;}
        choices_values[i]=minimax_evaluate(checkwin, square,team,team ,enemy,i,-1000000000,100000000);
//        dump_message(std::to_string(choices_values[i])+ " ");
    }

    for (int i=0; choices_values.size()>i;i++){
        dump_message(std::to_string(choices_values[i])+ " ");
        if (choices_values[i] >= choices_values[choice])
            choice = i;}
    dump_message(" | ");
    return choice;
}

int minimax_evaluate(std::function<int(std::vector<std::vector<char>> square,char team)> checkwin, std::vector<std::vector<char>> square,char player, char team, char enemy,int move,int alpha,int beta){
    function_calls++;
    if (function_calls>41){
        function_calls--;
        return 0;
    }
    if (square[0][move] ==team or square[0][move] ==enemy){
        function_calls--;
        return 0;}
    std::vector<std::vector<char>> new_square =square;
    new_square = make_move(square,move,player);
    int score =0;
    if (checkwin(new_square,team)==1){
        function_calls--;
        return 10;}
    else if (checkwin(new_square,enemy)==1){
        function_calls--;
        return -10;}
    else if (checkwin(new_square,team) == 0){
        function_calls--;
        return 0;}
    else if (checkwin(new_square,team) ==-1 and checkwin(new_square,team)==-1){
        int choice_player_score = -10000000;
        int choice_enemy_score = 10000000;
        int eval_score;
        std::vector<int> columnOrder=column_order(new_square[0].size());
        for(int i =0;i<new_square[0].size();i++){
            if (new_square[0][columnOrder[i]] != ' '){
                continue;}
            if (player == enemy){
                eval_score = minimax_evaluate(checkwin,new_square,team,team,enemy,columnOrder[i],alpha,beta);
                choice_player_score=std::max(eval_score,choice_player_score);
                alpha = std::max( alpha, choice_player_score);
                if (beta <= alpha){
                    function_calls--;
                    return choice_player_score;}

//                if (eval_score>choice_player_score){
//                    choice_player_score =eval_score;
//                }
            }
            else {
                eval_score = minimax_evaluate(checkwin,new_square,enemy,team,enemy,columnOrder[i],alpha,beta);
                choice_enemy_score=std::min(eval_score,choice_enemy_score);
                beta = std::min(beta, choice_enemy_score);
                if (beta <= alpha){
                    function_calls--;
                    return choice_enemy_score;}
//                if (eval_score<choice_enemy_score){
//                    choice_enemy_score =eval_score;
//                }
//                score += minimax_evaluate(checkwin,new_square,enemy,team,enemy,i);
            }
        }
        if (player == enemy)
            score =score+choice_player_score;
        else
            score = score+choice_enemy_score;
    }
    function_calls--;
    return score;
}


