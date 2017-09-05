// 3 Peg Tower of Hanoi Solution
// Written by Prof. Sreenivas for IE523: Financial Computing and
// GE523: Introduction to Discrete Event Systems

#include <iostream>
#include "hanoi.h"

int main (int argc, char * const argv[])
{
    int no_of_disks;
    
    // See 'hanoi.h' for the Towers class definition
    Towers x;
    
    std::cout << "Number of disks? ";
    std::cin >> no_of_disks;
    
    x.solve(no_of_disks);
}
