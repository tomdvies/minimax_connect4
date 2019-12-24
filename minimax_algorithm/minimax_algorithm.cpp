//
// Created by tom on 24/07/19.
//

#include "board.h"
#include "minimax_algorithm.hpp"
#include "connect4_curses.hpp"
#include <vector>
#include <fstream>
#include <map>

std::map<std::string, int> boardEnemyMinimax;
std::map<std::string, int> boardTeamMinimax;
int function_calls = 0;

int minimax_evaluate(Board square,char player, char team, char enemy,int move);
void dump_message(std::string message);
int minimax_evaluate(Board square,char player, char team, char enemy,int move,int alpha,int beta);
std::string boardKey(Board board);
int cachedEvaluate(Board square,char player, char team, char enemy,int move,int alpha,int beta);
Board make_move(Board board,int move,char player);


std::string boardKey(Board board){
    std::string key;
    for(int i =0;i<board.size();i++){
        for (char &c: board[i])
            key+=(c==' ') ? '-' : c;
    }
    return key;
}




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

void dump_message(int message){
    std::ofstream outfile;
    outfile.open("dumped_values.txt", std::ios_base::app);
    outfile << message;
    outfile << " ";
}

Board make_move(Board board,int move,char player){
    Board new_board = board;
    for (int i =0; i<board.size();i++){
        if (board[i][move]!=' '){
            return new_board;
        }
        new_board=board;
        new_board[i][move]=player;
    }
    return new_board;
}

int choice_minimax(Board square, char team, char enemy) {
    function_calls=0;
    boardTeamMinimax.clear();
    boardEnemyMinimax.clear();
    Board new_square = square;
    std::vector<int> choices_values(square[0].size(),0);
    int choice =1;
//    choices_values.


    for (int i=0; square[0].size() > i; i=i+1){
        if (square[0][i] ==team or square[0][i] ==enemy){choices_values[i] = -1000000000;continue;}
        choices_values[i]=cachedEvaluate(square,team,team ,enemy,i,-1000000000,100000000);
//        dump_message(std::to_string(choices_values[i])+ " ");
    }

    for (int i=0; choices_values.size()>i;i++){
        dump_message(std::to_string(choices_values[i])+ " ");
        if (choices_values[i] > choices_values[choice])
            choice = i;}
    dump_message(" | ");
    return choice;
}


int cachedEvaluate(Board square,char player, char team, char enemy,int move,int alpha,int beta){
    Board new_square;
    new_square = make_move(square,move,player);
    std::string key= boardKey(new_square);
    if (player == enemy){
        if (boardEnemyMinimax.count(key) == 0){
            function_calls++;
            boardEnemyMinimax[key] = minimax_evaluate(new_square,player,team,enemy,move,alpha,beta);
            function_calls--;
        }
        return boardEnemyMinimax[key];
    }
    if (player == team){
        if (boardTeamMinimax.count(key) == 0){
            function_calls++;
            boardTeamMinimax[key] = minimax_evaluate(new_square,player,team,enemy,move,alpha,beta);
            function_calls--;
        }
        return boardTeamMinimax[key];
    }

}


int minimax_evaluate(Board square,char player, char team, char enemy,int move,int alpha,int beta){
    if (square[0][move] !=' '){
        return 0;}
//    if (function_calls>41){
//        function_calls--;
//        return 0;
//    }
    Board new_square =square;
//    new_square = make_move(square,move,player);
    int score =0;
    dump_message(function_calls);
    if (checkwin(new_square,team)==1){
        return 10;}
    else if (checkwin(new_square,enemy)==1){
        return -10;}
    else if (checkwin(new_square,team) == 0){
        return 0;}
    else if (checkwin(new_square,team) ==-1 and checkwin(new_square,enemy)==-1){
        int choice_player_score = 0;
        int choice_enemy_score = 0;
        int eval_score;
//        std::vector<int> columnOrder=column_order(new_square[0].size());
        for(int i =0;i<new_square[0].size();i++){
            if (new_square[0][i] != ' '){
                continue;
            }

            if (player == enemy){
                if (i==0) {
                    choice_player_score = cachedEvaluate(new_square,team,team,enemy,i,alpha,beta);
                    eval_score = choice_player_score;
                }

                else{
                    eval_score = cachedEvaluate(new_square,team,team,enemy,i,alpha,beta);
                }

                choice_player_score=std::max(eval_score,choice_player_score);
//                alpha = std::max( alpha, choice_player_score);
//                if (beta <= alpha){
//                    function_calls--;
//                    return choice_player_score;}

//                if (eval_score>choice_player_score){
//                    choice_player_score =eval_score;
//                }
            }
            else {
                if (i==0) {
                    choice_enemy_score = cachedEvaluate(new_square,enemy,team,enemy,i,alpha,beta);
                    eval_score = choice_enemy_score;
                }
                else{
                    eval_score = cachedEvaluate(new_square,enemy,team,enemy,i,alpha,beta);
                }
                choice_enemy_score=std::min(eval_score,choice_enemy_score);
//                beta = std::min(beta, choice_enemy_score);
//                if (beta <= alpha){
//                    function_calls--;
//                    return choice_enemy_score;}
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

    return score;
}


