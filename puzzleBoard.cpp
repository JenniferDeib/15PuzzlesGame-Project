/*
Student number:2669053
Name and surname:Jennifer Deib
Date:6 May 2024

Project title: 15 Puzzles Game

File description: puzzleBoard CPP File of the ELEN2024 Project
*/

#include "puzzleBoard.h"
#include <iostream>
#include <fstream>
#include <string>


//constructor of class
puzzleBoard::puzzleBoard()
{
    //
}

int puzzleBoard::getvalues(int rows,int cols,int maxMoves)
{
    return rows;//variable to represent the rows of the puzzle
    return cols;//variable used to represent the cols of the puzzle
    return maxMoves;//variable that represents the maximum number of moves
}

//function used for debugging purposes and not for direct use in the project.
void puzzleBoard::display_Puzzle(int puzzle[][4],int rows,int cols)
{
    for (int i = 0; i < rows; ++i)  //iterates through each row and col through a nested for loop to display the puzzle board
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << puzzle[i][j] << " ";// display the board with correct spacing
        }
        cout << endl;
    }

    cout << endl;// allows a neat layout to separate the respective boards
}

bool puzzleBoard::moveUp(int arr[][4], int rows, int cols, int spaceRow, int spaceCol)//user-defined function that will allow move up motion.
{
    if ( spaceRow > 0 && spaceRow < rows )//ensures that the move up is not out of bounds and is a valid move
    {
        swap(arr[spaceRow][spaceCol], arr[spaceRow - 1][spaceCol]);//that row will only be affected by the move up hence the changes will only be made to the rows.
        return true;//if the rows is greater that zero and has space to move up it is valid
    }
    return false;
}

bool puzzleBoard::moveDown(int arr[][4], int rows, int cols, int spaceRow, int spaceCol)//user-defined function that will allow move down motion.
{
    if ( spaceRow >= 0 && spaceRow + 1 < rows)//ensures that the move is not out of bounds and only affects rows
    {
        swap(arr[spaceRow][spaceCol], arr[spaceRow + 1][spaceCol]);//move down
        return true;//if the rows have 3 spaces below or 2 or 1 it is valid not more than that
    }
    return false;
}

bool puzzleBoard::moveLeft(int arr[][4], int rows, int cols, int spaceRow, int spaceCol)//user-defined function that will allow move left motion.
{
    if ( spaceCol > 0 && spaceCol < cols)//checks if the move is valid and not out of bounds and affects the columns only
    {
        swap(arr[spaceRow][spaceCol], arr[spaceRow][spaceCol - 1]);
        return true;
    }
    return false;

}

bool puzzleBoard::moveRight(int arr[][4], int rows, int cols, int spaceRow, int spaceCol)//user-defined function that will allow move right motion.
{

    if (spaceCol >= 0 && spaceCol + 1 < cols)//checks if move is valid and not out of bounds.
    {
        swap(arr[spaceRow][spaceCol], arr[spaceRow][spaceCol + 1]);
        return true;    //Return true if we managed to make a move, otherwise false;
    }
    return false;
}


bool puzzleBoard::PuzzleSolved(int puzzle[][4], int rows, int cols)   //user-defined function that ensures the puzzle if in a solved state.
{
    int num = 1 ;//goes through each element in puzzle to ensure that it is from 1 to 15 in numerical order with the blank space last position
    for (int i=0 ; i < rows ; i ++)  //allows the search of each element in the matrix
    {
        for ( int j= 0 ; j < cols ; j ++)
        {
            if (puzzle[i][j]!= num&&!(i==rows -1 && j== cols -1 &&puzzle [i][j]==-1))   // conditions of code to ensure correct order...
            {
                return false ;//checks if in numerical order and if the last element in the game is not -1 the puzzle will not be solved.
            }
            num++ ;//checks each element
        }
    }
    return true ;
}

bool puzzleBoard::is_solvable(int puzzle[][4]) //user-defined function that checks is a puzzle is solvable or not
{
    int board[16];//array for the board to check
    int index=0;
    int num_inversions=0;
    int rowempty;

    for(int i =0 ; i<4 ; i ++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            board[index++]= puzzle[i][j];//nested loop grants access to the 2D array

            if(puzzle[i][j] == -1)
                rowempty = i;
        }
    }

    for(int i = 0 ; i<16 ; i ++) //calculates the total number of inversion each tile has in order to check if it is solvable or not
    {
        for(int j = i+1 ; j < 16 ; j++)
            if(board[i]!= -1 && board[j]!=-1 && board[i]>board[j])
            {
                num_inversions++;//get the number total counts of inversions
            }
    }

    //if blank position is in even row from bottom:inversions must be odd
    //if blank position is in odd row from bottom :inversions must be even
    if((num_inversions%2==0) && (rowempty%2 == 0))
    {
        return false;
    }
    else if((num_inversions%2==1) && (rowempty%2 == 1))
    {
        return false;
    }
    return true;
}

int puzzleBoard::manhattan(int puzzle[][4])//user-defined function that allows the calculation of the manhattan distance.
{
    int num=0;//number of inversions
    int r=0;//correct row
    int c=0;//correct column
    int manhattan_distance = 0;//variable for the manhattan distance
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            num = puzzle[i][j];

            // The -1 is to be ignored
            if (num == -1)
                continue;

            // Calculate the correct position (row and column) of the number in a solved board
            r = (num - 1) / 4;
            c = (num - 1) % 4;

            // Add the absolute horizontal and vertical distances into the overall Manhattan distance
            manhattan_distance += abs(r - i);
            manhattan_distance += abs(c - j);


        }
    }

    return manhattan_distance;
}


