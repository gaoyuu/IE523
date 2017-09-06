//
//  hint.h
//  N Queens Problem
//
//  Created by Ramavarapu Sreenivas on 8/23/16.
//

//
//HW 1  First part Gengxiao Li
//reference from http://www.geeksforgeeks.org/backtracking-set-3-n-queen-problem/

#ifndef N_queens
#define N_queens
using namespace std;
class Board
{
    
    // private data member: size of the board
    int size;
    
    // pointer-to-pointer initialization of the board
    int **chess_board;
    
    // private member function:  returns 'false' if
    // the (row, col) position is not safe.
    bool is_this_position_safe(int row, int col)
    {
        // write the appropriate code on your own that returns
        // "true" if the (row,col) position is safe.  If it is
        // unsafe (i.e. some other queen can threaten this position)
        int a,b;
        /*since the algorithm has been solved by col++, when we look at one column,
         if there is no Queen of all the rows of that column, then it will be temporatorily safe,
         if there is one Queen, it will be dangerous*/
        
        for( a=0;a<=col-1;a++){
            if (chess_board[row][a])
                return false;
        }
        /*Here I check the upper left corner for the chess_board*/
        for(a=row, b= col; a==0 && b==0; a--, b--){
            if(chess_board[a][b])
                return false;
        }
        /*Then check the the lower left corner   */
        for (a=row,b=col; a==size-1 && b==0; a++,b--){
            if(chess_board[a][b])
                return false;
        }
        return true;
    }
    
    // private member function: initializes the (n x n) chessboard
    void initialize(int n)
    {
        size = n;
        chess_board=new int* [n];
        for(int i=0; i<=size-1; i++){
            
            chess_board[i]=new int[n];
        }
        
        for(int j=0; j<=size-1; j++)
            for(int k=0; k<=size-1; k++){
                chess_board[j][k]=0;
            }
        
        // write the appropriate code that uses the pointer-to-pointer
        // method to initialize the (n x n) chessboard.  Once initialized,
        // put zeros in all entries.  Later on, if you placed a queen in
        // the (i,j)-th position, then chessboard[i][j] will be 1.
    }
    
    // private member function: prints the board position
    void print_board()
    {
        std::cout << size << "-Queens Problem Solution " << std::endl;
        for (int k = 0; k < size; k++)
            std::cout << "---" ;
        std::cout << std::endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                if (chess_board[i][j] == 1)
                    cout << " Q ";
                else
                    cout << " - ";
            cout << endl;
        }
        for (int k = 0; k < size; k++)
            std::cout << "---" ;
        cout << endl;    }
    
    // private member function: recursive backtracking
    bool solve(int col)
    {
        // implement the recursive backtracking procedure described in
        // pseudocode format in figure 1 of the description of the first
        // programming assignment
        if (col >= size)
            return true;
        else
            for(int i=0;i<=size-1;i++){
                if (is_this_position_safe(i, col)){
                    /*Place queen at (row, column)-position in the n × n chessboard.*/
                    
                    chess_board[i][col]=1;
                    if (solve(col+1))
                        return true;
                    else
                    /*Remove queen at (row, column)-position in the n × n chessboard.
                     Placing it here was a bad idea.*/
                        chess_board[i][col]=0;
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
#endif /* N_queens_h */
