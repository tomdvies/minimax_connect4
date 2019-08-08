//
// Created by tom on 24/07/19.
//

#include "minimax_algorithm.hpp"
#include <vector>
#include <fstream>

int function_calls = 0;

int minimax_evaluate(std::function<int(std::vector<char> square,char team)> checkwin, std::vector<char> square,char player, char team, char enemy,int move);

void dump_message(std::string message){
    std::ofstream outfile;
    outfile.open("dumped_values.txt", std::ios_base::app);
    outfile << message;
}

int choice_minimax(std::function<int(std::vector<char> square,char team)> checkwin, std::vector<char> square, char team, char enemy) {
    std::vector<char> new_square = square;
    std::vector<int> choices_values(9,0);
    int choice =1;
//    choices_values.


    for (int i=0; square.size() > i; i=i+1){
        if (square[i] ==team or square[i] ==enemy){choices_values[i] = -100000000;continue;}
        choices_values[i]=minimax_evaluate(checkwin, square,team,team ,enemy,i);

    }

    for (int i=0; choices_values.size()>i;i++){
        dump_message(std::to_string(choices_values[i])+ " ");
        if (choices_values[i] >= choices_values[choice-1])
            choice = i+1;}
    dump_message(" | ");
    return choice;
}

int minimax_evaluate(std::function<int(std::vector<char> square,char team)> checkwin, std::vector<char> square,char player, char team, char enemy,int move){
    function_calls++;
    if (square[move] ==team or square[move] ==enemy){
        function_calls--;
        return 0;}
    std::vector<char> new_square = square;
    new_square[move] =player;
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
        for(int i =0;i<new_square.size();i++){
            if (new_square[i] ==team or new_square[i] == enemy)
                continue;
            if (player == enemy){
                eval_score = minimax_evaluate(checkwin,new_square,team,team,enemy,i);
                if (eval_score>choice_player_score){
                    choice_player_score =eval_score;
                }}
            else {
                eval_score = minimax_evaluate(checkwin,new_square,enemy,team,enemy,i);
                if (eval_score<choice_enemy_score){
                    choice_enemy_score =eval_score;
                }
//                score += minimax_evaluate(checkwin,new_square,enemy,team,enemy,i);
            }
        }
        if (player == enemy)
        score =score+choice_player_score;
        else score = score+choice_enemy_score;
    }
    function_calls--;
    return score;
}


