/*
Student number:2669053
Name and surname:Jennifer Deib
Date:6 May 2024

Project title: 15 Puzzles Game

File description: Algorithm header File of the ELEN2024 Project
*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include "puzzleBoard.h"


class Algorithm
{
public://function declarations that is allowed use from the client.
    Algorithm();//constructor function of the algorithm header file
    void IDA_starr(int arr[][4], int rows, int cols, int puzzleNum);//function declaration of the IDA* algorithm
    int search_path(int puzzle[][4], int g, int prevMove = -1);//function declaration that calculates the shortest distance
    vector<string> getMoves();//function declaration that stores the moves in a vector of strings

private://functions and variables that is not allowed direct use from the client
    void copyPuzzle(int old[][4], int newP[][4]);//function declaration of copy puzzle to ensure correct moves are made
    pair<int, int> findTheSpace(int puzzle[][4]);//function declaration that will find the blank space position initially.
    puzzleBoard board; //This will autamigically call the default constructor
    //private variables:
    vector<string> moves;   //stores moves in a vector.
    int boundaryValue;     //variable represents the boundary value
    int minimumCost;      //variable that was used to get the best move in relation to the minimum cost calculated
    int puzzleNumber;    //variable that was used to represent the number of puzzle being solved
    int maxMoves;       //variable that represents the maximum allowed -1000 moves
    bool maxMovesExceeded; //variable checks if the maximum moves has been exceeded or not.
};

#endif // ALGORITHM_H
// search function
