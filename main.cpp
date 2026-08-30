/*
Student number:2669053
Name and surname:Jennifer Deib
Date:6 May 2024

Project title: 15 Puzzles Game

File description: Main CPP File of the ELEN2024 Project
*/

#include <iostream>//header file used to have input and output access via the console
#include <fstream>// header file that allows you to read / write from text files
#include <string> // allows the use of strings and get line  function to display the array.
#include <vector> //header file allows the use of vectors
#include "puzzleBoard.h"//header file that creates the board state
#include "Algorithm.h"//header file for the IDA* algorithm to solve the puzzle.


using namespace std;

int main()

{
    //cout<<"Final";

    //define files
    ifstream inData;
    ofstream outData;
    //open files
    inData.open("input.txt");
    outData.open("output.txt");
    //checks if there was an error opening the files
    if (!inData|| !outData)
    {
        cout << "Cannot open the input file. ";
        cout << "The program terminates." << endl;
        return 1;
    }
    //declare variables
    const int rows = 4;
    const int cols = 4;
    int puzzle_num=1;
    int number;
    int i = 0;
    int j = 0;
    //declare the board as a 2D array//stores the input data
    int puzzle[rows][cols];


    //read from the input file to ensure correct output
    Algorithm algorithm;//class object orientation
    vector<string> moves;//stores moves
    //reads in data from input file and store it in an array
    while (inData >> number)
    {
        //stores data in a 2D array
        puzzle[i][j] = number;

        j++;
        if (j > 3)
        {
            j =0;
            i++;
        }

        if (i == 4)
        {   //testing purposes
            puzzleBoard board;
            //board.display_Puzzle(puzzle,rows,cols);
            i =0;
            //implements the IDA star algorithm to program via an object of the class
            algorithm.IDA_starr(puzzle, 4, 4, puzzle_num);
            puzzle_num++;//will increase when a new puzzle in read from the input text file
            //gets the moves via a object of the class (note moves stored in a vector of strings)
            moves = algorithm.getMoves();
            //range based loop to keep track of the amount of moves made
            for(string move_ : moves)
            {
                outData << move_ << endl;//will display the amount of moves made
            }
            outData << endl;
        }
    }

//close files
    inData.close();
    outData.close();

    return 0;
}
