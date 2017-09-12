//
//  Sudoku_all.h
//  test1
//
//  Created by Yu Gao on 9/7/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

#ifndef sudokuc
#include <vector>
#include <fstream>
using std::vector;
using namespace std;

class Sudoku
{
    // Private
    int puzzle[9][9];
    
    //initialize a private int k. The number is used to be filled in the puzzle
    int k;
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row, int num)
    {
        // write code that checks if "row" is valid
        for (int col = 0; col < 9; col++)
            if (puzzle[row][col] == num)
                return true;
        return false;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col, int num)
    {
        // check validity of "col"
        for (int row = 0; row < 9; row++)
            if (puzzle[row][col] == num)
                return true;
        return false;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    // modify original call name row&col to uprow&leftcol.
    // for block check, set the start point to up-left conner of a 3 by 3 box
    bool block_valid(int uprow, int leftcol, int num)
    {
        // check 3 x 3 block validity
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (puzzle[i+uprow][j+leftcol] == num)
                    return true;
        return false;
        
    }
    
    // function call to check whether the puzzle is done,
    // true if is done, false if still has node remain to be filled
    bool is_done(int &row, int &col)
    {
        bool result = true;
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (puzzle[row][col] == 0)
                    return false;
        return result;
    }
    
    // function call to check whether a pivot is safe
    bool is_safe(int row, int col, int num)
    {
        return !row_valid(row, num) &&
        !col_valid(col, num) &&
        !block_valid(row - row % 3 , col - col % 3, num);
    }
    
    // function call to check whether the puzzle is done,
    // different with the is_done, this accept a bard
    bool is_board_done(int puzzle[9][9])
    {
        bool result = true;
        for (int row = 0; row < 9; row++)
            for (int col = 0; col < 9; col++)
                if (puzzle[row][col] == 0)
                    return false;
        return result;
    }
public:
    
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        ifstream input(argv[1]) ;
        if ( !input.is_open())
        {
            cout << "File not existed in current rep" << endl;
            exit(1);
        }
        
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                input >> puzzle[i][j];
            }
        }
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        if (!is_board_done(puzzle))
            std::cout << std::endl << "initial Board Position" << std::endl;
        
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        //initialize a temp to store the solution number
        static int temp = 0;
        
        if (is_done(row, col))
        {
            cout << endl;
            cout << "solution #: " << ++temp << endl;
            print_puzzle();
            return true;
        }
        
        for (int k = 1; k <= 9; k++)
        {
            
            if (is_safe(row, col, k))
            {
                // make tentative assignment
                puzzle[row][col] = k;
                
                Solve(row, col);
                
            }
            puzzle[row][col] = 0;
        }
        
        return false; // this triggers backtracking
    }
    // this part of the code identifies the row and col number of the
    // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
    // no zeros, the variable row will be 9 => the puzzle is done, as
    // each entry is row-, col- and block-valid...
    // use the pseudo code of figure 3 of the description
};

#endif
