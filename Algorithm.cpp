/*
Student number:2669053
Name and surname:Jennifer Deib
Date:6 May 2024

Project title: 15 Puzzles Game

File description: Algorithm cpp File of the ELEN2024 Project
*/

#include "Algorithm.h"
#include "puzzleBoard.h"


//contructor
Algorithm::Algorithm()//Algorithm constructor
{
    maxMoves = 1000;//the restriction of moves
    maxMovesExceeded = false;//false as can never reach 1000 for the first move
}

vector<string> Algorithm::getMoves()
{
    return moves;//stores the moves
}

void Algorithm::copyPuzzle(int old[][4], int newP[][4])//makes a copy of the puzzle to check moves made
{
    for(int col = 0; col < 4; col++)//loops through rows and cols to make new puzzle a copy
    {
        for(int row = 0; row < 4; row++)
        {
            newP[col][row] = old[col][row];//copies the previous puzzle
        }
    }
}

pair<int, int> Algorithm::findTheSpace(int puzzle[][4])//find the blank space of the intitial state of the puzzle
{
    int spaceRow = -1;//position of blank
    int spaceCol = -1;
    int puzzleSize = 4;
    // Loop through the array to search for the target element
    for (int row = 0; row < puzzleSize; ++row) {
        for (int col = 0; col < puzzleSize; ++col) {
            if (puzzle[row][col] == -1) {
                // Assuming we only want to move one occurrence, return after the move
                spaceRow = row;
                spaceCol = col;
            }
        }
    }
    return make_pair(spaceRow, spaceCol);
}


void Algorithm::IDA_starr(int puzzle[][4],int rows, int cols, int puzzleNum) //Function that will solve the game
{
    puzzleNumber = puzzleNum;//the puzzle that is read from the text file
    moves.clear();//clears all the moves when a new puzzle is being solved
    maxMovesExceeded = false;//when the game starts it will not be at 1000 moves

    if(board.is_solvable(puzzle) == false)//checks if the puzzle is solvable or not
    {
        string line = to_string(puzzleNum) + ", not solvable";//if false return this statement to the output(not solvable)
        moves.push_back(line);//will put this line after the number (pushes it to the end of the vector)
        return;
    }

    //cout<<bound << "\n";
    boundaryValue = board.manhattan(puzzle);//makes the bound value the calculated value in the manhattan distance
    minimumCost = INT_MAX;//sets the minimum cost to the max value
    int movesSoFar = 0;//you will start with zero moves first
    while(true)
    {
        int cost = search_path(puzzle, movesSoFar);//checks for the best move according to the search function

        if (cost==-1)//will return -1 if best move ,hence best move will be made
        {
            return;
        }

        if(maxMovesExceeded)//if more that 1000 moves it will not solve due to the restriction
        {
            string line = to_string(puzzleNum) + ", solvable, not solved, " + to_string(maxMoves);//will display the puzzle number not solved in amount of moves
            moves.push_back(line);
            return;
        }

        boundaryValue = minimumCost;//sets the bound equal to the min cost//as it will check a better move
        minimumCost = INT_MAX;//makes the minimum cost the max
    }
}

int Algorithm::search_path(int puzzle[][4], int g, int prevMove)
{
    int rows = 4;//4x4matrix
    int cols = 4;

    if(g > maxMoves)//if the g cost greater than 1000
    {
        maxMovesExceeded = true;//the max moves will be true
        return 0;
    }

    if (board.PuzzleSolved(puzzle, rows, cols))  //checks if puzzle has been solved or not
    {
        //return true;
        //board.display_Puzzle(puzzle, 4,4);

        string firstLine = to_string(puzzleNumber) + ", solvable, solved, " + to_string(moves.size()) + ":";//if solved will display puzzle num,the statement and the amount of moves
        moves.insert(moves.begin(), firstLine);
        return -1;
    }

    int f = board.manhattan(puzzle) + g;//recursive call ,num moves +manhattan distance to check another search route

    if(f > boundaryValue)
    {
        return f;//setting a new bound
    }

    // Declare Move outside the loop
    //board.display_Puzzle(puzzle, 4 ,4);
    int moveNumber = -1; //set to negative one so that does not have to be part of arguements if not necessary
    string move_ = "";
    pair<int, int> space;//can hold two integers,row index ;then the col index
    for (int i= 0; i <= 3; i++)  //possible moves
    {
        int newPuzzle[4][4];
        bool moveMade = false;//no move being made

        copyPuzzle(puzzle, newPuzzle);//checks move after being made


        if (i == 0)
        {
            //move(puzzle )
            if(prevMove == 1) continue; //If previous move was down, next move can't be up
            space = findTheSpace(newPuzzle);//finds the blank position
            moveMade = board.moveUp(newPuzzle, rows, cols, space.first, space.second);//if the move is up=0
            space.first = space.first - 1;//the rows are affected hence the space.first.We are looking at the valued tile moves and not blank space
            move_ = "D";//opposite to negative one(valued tile)
            moveNumber = 0;//to identify the moves when a move has been made already
        }
        else if (i == 1)
        {
            if(prevMove == 0) continue; //This prevents undoing our previous moves which would create and infinite loop
            space = findTheSpace(newPuzzle);
            moveMade = board.moveDown(newPuzzle, rows, cols, space.first, space.second);//if move is down=1
            space.first = space.first + 1;//move up for the valued tile
            move_ = "U";//opposite to the blank tile
            moveNumber = 1;
        }
        else if (i == 2)
        {
            if(prevMove == 3) continue;//This prevents it from going in a continuous loop
            space = findTheSpace(newPuzzle);
            moveMade = board.moveLeft(newPuzzle, rows, cols, space.first, space.second);//if move is left=2
            space.second = space.second - 1;
            move_ = "R";
            moveNumber = 2;
        }
        else if (i == 3)
        {
            if(prevMove == 2) continue;
            space = findTheSpace(newPuzzle);
            moveMade = board.moveRight(newPuzzle, rows, cols, space.first, space.second);//if move is right=3
            space.second = space.second + 1;
            move_ = "L";
            moveNumber = 3;
        }

        //Check that the computer actually managed to move before we store the move
        if(moveMade == true)//if a move occurs
        {
            move_ = to_string(space.first) + " " + to_string(space.second) + " " + move_;//the index position of the move
            moves.push_back(move_);//stores the moves in a vector
            int value = search_path(newPuzzle, g + 1, moveNumber);//a move occured ,new move will be searched for after

            if(value==-1)
            {
                return -1;
            }
            else if(value < minimumCost) //ensures first move is made
            {
                minimumCost = value;//best move made
            }

            if(g > maxMoves)
            {
                maxMovesExceeded = true;
                return 0;
            }

            moves.pop_back();
        }
    }
    // Return something here
    return minimumCost; // Return value for now, replace with appropriate return value
}








