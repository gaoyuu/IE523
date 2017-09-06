//
//  sudoku.h
//  Sudoku
//
//  Created by Yu Gao on 9/5/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//
/*
 *  sudoku.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
 */

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row)
    {
        // write code that checks if "row" is valid
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col)
    {
        // check validity of "col"
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // check 3 x 3 block validity
    }
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        std::cout << std::endl << "Board Position" << std::endl;
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
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as 
        // each entry is row-, col- and block-valid...
        
        // use the pseudo code of figure 3 of the description
    }
};

#endif
