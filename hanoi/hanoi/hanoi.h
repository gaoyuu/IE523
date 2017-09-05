// hanoi.h
// Written by Prof. Sreenivas for IE523/GE523

#ifndef HANOI_H
#define HANOI_H

#include <cmath>
#include <deque>

using std::deque;

class Towers
{
    // private data member: #steps taken so far
    int number_of_steps;
    
    // private data member: #disks on 1st Peg
    int number_of_disks;
    
    // private data member: 3-Deques-of-Deques
    // towers[0] is deque for the 1st Peg, towers[1] is the deque
    // for the 2nd Peg, towers[2] is the deque for the 3rd Peg
    deque < deque <int> > towers;
    
    // private member function:  returns 'false' if a larger disk
    // is moved on top of a smaller disk during a move
    bool is_everything_legal ()
    {
        bool result = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < towers[i].size(); j++)
                for (int k = j; k < towers[i].size(); k++)
                    if (towers[i][k] < towers[i][j]) {
                        result = false;
                    }
        return (result);
    }
    
    // private member function: initializes the disks on Peg 1
    void initialize(int n)
    {
        number_of_steps = 0;
        number_of_disks = n;
        for (int i = 0; i < n; i++)
            towers[0].push_back(i+1);
    }
    
    // private member function: primitive/basic move of the top disk
    // from the source peg to the destination peg -- and legality-check
    void move_top_disk(int source, int dest)
    {
        number_of_steps++;
        std::cout << "Move disk " << towers[source].front() << " from Peg ";
        std::cout << source+1 << " to Peg " << dest+1;
        towers[dest].push_front(towers[source].front());
        towers[source].pop_front();
        if (true == is_everything_legal())
            std::cout << " (Legal)" << std::endl;
        else
            std::cout << " (Illegal)" << std::endl;
    }
    
    // private member function: recursive solution to the 3 Peg Tower of Hanoi
    void move(int number_of_disks, int source, int dest, int intermediate)
    {
        if (1 == number_of_disks)
            move_top_disk (source, dest);
        else {
            move (number_of_disks-1, source, intermediate, dest);
            move_top_disk (source, dest);
            move (number_of_disks-1, intermediate, dest, source);
        }
    }
    
    // private member function: prints the state of Peg m (m = 0, 1, 2)
    void print_peg_state(int m)
    {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "State of Peg " << m+1 << " (Top to Bottom): ";
        for (int i = 0; i < towers[m].size(); i++)
            std::cout << towers[m][i] << " ";
        std::cout << std::endl;
        std::cout << "Number of Steps = " << number_of_steps << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
public:
    // Constructor: creates 3 deques (one for each Peg)
    Towers()
    {
        for (int i = 0; i < 3; i++) 
        {
            deque <int> peg;
            towers.push_back(peg);
        }
    }	
    
    // Solves the 3 Peg Tower of Hanoi
    void solve(int m)
    {
        initialize(m);
        print_peg_state(0);
        move(m, 0, 2, 1);
        print_peg_state(2);
    }
};
#endif
