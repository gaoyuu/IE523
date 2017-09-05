//
//  N_queens_all.h
//  N_queens_all
//
//  Created by Yu Gao on 9/3/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

//
//  hint.h
//  N Queens Problem
//
//  Created by Ramavarapu Sreenivas on 8/23/16.
//
//

#ifndef N_queens_all
#define N_queens_all
using namespace std;

class Board
{
    
    // private data member: size of the board
    int size;
    
    // pointer-to-pointer initialization of the board
    int **chess_board;
    
    // private member function:  returns 'false' if
    // the (row, col) position is not safe.
    bool is_this_position_safe (int row, int col)
    {
        bool result = true;
        int i,j;
        
        // Check this row on left side
        for (i = 0; i < col; i++)
            if (chess_board[row][i])
                return false;
        
        /* Check upper diagonal on left side */
        for (i = row, j = col; i>=0 && j>=0; i--, j--)
            if (chess_board[i][j])
                return false;
        
        /* Check lower diagonal on left side */
        for (i = row, j = col; j>=0 && i < size; i++, j--)
            if (chess_board[i][j])
                return false;
        return result;
        
    }
    
    // private member function: initializes the (n x n) chessboard
    void initialize(int n)
    {
        size = n;
        chess_board = new int*[n];
        
        for (int i = 0; i < n; i++)
            chess_board[i] = new int[n];
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                chess_board[i][j] = 0;
            }
        
        // write the appropriate code that uses the pointer-to-pointer
        // method to initialize the (n x n) chessboard.  Once initialized,
        // put zeros in all entries.  Later on, if you placed a queen in
        // the (i,j)-th position, then chessboard[i][j] will be 1.
    }
    
    // private member function: prints the board position
    void print_board()
    {
        std::cout << size << "-Queens Problem Solution" << std::endl;
        for (int k = 0; k < size; k++)
            std::cout << "---" ;
        std::cout << std::endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                cout << " " << chess_board[i][j] << " ";
            cout << endl;
        }
        for (int k = 0; k < size; k++)
            std::cout << "---" ;
        cout << endl;
    }
    
    // private member function: recursive backtracking
    bool solve(int col)
    {
        if (col >= size)
            return true;
        
        /* Consider this column and try placing
         this queen in all rows one by one */
        for (int i = 0; i < size; i++)
        {
            /* Check if queen can be placed on
             board[i][col] */
            if ( is_this_position_safe(i, col))
            {
                /* Place this queen in board[i][col] */
                chess_board[i][col] = 1;
                
                /* recur to place rest of the queens */
                if (solve(col + 1))
                    return true;
                
                /* If placing queen in board[i][col]
                 doesn't lead to a solution, then
                 remove queen from board[i][col] */
                chess_board[i][col] = 0; // BACKTRACK
            }
        }
        return false;
    }
    
public:
    // Solves the n-Queens problem by (recursive) backtracking
    void nQueens(int n)
    {
        initialize(n);
        
        if (solve(0))
            print_board();
        else
            std::cout << "There is no solution to the " << n << "-Queens Problem" << std::endl;
    }
};
#endif
