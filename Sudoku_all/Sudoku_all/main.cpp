//
//  main.cpp
//  test1
//
//  Created by Yu Gao on 9/7/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

#include <iostream>
#include "Sudoku_all.h"

using namespace std;

int main (int argc, char * const argv[])
{
    Sudoku x;
    x.read_puzzle(argc, argv);
    cout << "Input file name : " << argv[1] << endl;
    x.print_puzzle();
    x.Solve(0,0);
    //x.alternate_Solve(0, 0);
    //x.print_puzzle();
    
    return 0;
}
