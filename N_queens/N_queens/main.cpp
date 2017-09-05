//
//  main.cpp
//  N_queens
//
//  Created by Yu Gao on 9/3/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

// N Queens Problem via (Backtracking, which is implemented by) Recursion
// Written by Prof. Sreenivas for IE523: Financial Computing

#include <iostream>
#include "N_queens.h"

int main (int argc, char * const argv[])
{
    Board x;
    
    int board_size;

    sscanf (argv[1], "%d", &board_size);

    x.nQueens(board_size);
    
    return 0;
}
