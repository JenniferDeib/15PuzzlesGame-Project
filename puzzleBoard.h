/*
Student number:2669053
Name and surname:Jennifer Deib
Date:6 May 2024

Project title: 15 Puzzles Game

File description: puzzleBoard header File of the ELEN2024 Project
*/

#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H


using namespace std;

class puzzleBoard {
public://functions that can be accessed by the client
    puzzleBoard();//constructor function
    void display_Puzzle(int puzzle[][4], int rows, int cols);//function declaration used for displaying the board
    int getvalues(int rows,int cols,int maxMoves);//function declaration used to get a private variables.
    bool moveUp(int arr[][4], int rows, int cols, int row, int col);//function declaration for moving up .
    bool moveDown(int arr[][4], int rows, int cols, int row, int col);//function declaration for moving down.
    bool moveLeft(int arr[][4], int rows, int cols, int row, int col); // function declaration for moving left.
    bool moveRight(int arr[][4], int rows, int cols, int row, int col);//function declaration for moving right.
    bool PuzzleSolved(int puzzle[][4], int rows, int cols);//function declaration used to check the game is over.
    bool is_solvable(int puzzle[][4]);//function declaration for the solvable check.
    int manhattan(int puzzle[][4]) ;//function declaration for the manhattan distance calculation

private://variables that are used but cannot be directly accessed ,prevents global variables.
    int rows;
    int cols;
    int maxMoves;
};

#endif // PUZZLEBOARD_H
