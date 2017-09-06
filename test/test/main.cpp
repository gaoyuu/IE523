// N Queens Problem via (Backtracking, which is implemented by) Recursion
// Written by Prof. Sreenivas for IE523: Financial Computing

#include <iostream>
#include "N_queens.h"
using namespace std;
int main (int argc, char * const argv[])
{
    Board x;
    
    int board_size;
    sscanf (argv[1], "%d", &board_size);
    //cin>>board_size;
    
    x.nQueens(board_size);
    
    return 0;
}

