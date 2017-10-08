//
//  main.cpp
//  linear_algebra3
//
//  Created by Yu Gao on 10/8/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

// Illustration of concepts from Linear Programming using the NEWMAT library
// Written by Prof. R.S. Sreenivas for IE523: Financial Computation

#include <iostream>
#include <iomanip>
#include <cmath>
#include "/Users/gaoyu/Documents/Courses/newmat11/newmatap.h"
#include "/Users/gaoyu/Documents/Courses/newmat11/newmat.h"
#include "/Users/gaoyu/Documents/Courses/newmat11/newmatio.h"

#define EPSILON 0.0000001

// This routine computes the rank of a matrix by counting the number of
// non-zero singular-values of the matrix.
// See http://en.wikipedia.org/wiki/Singular_value_decomposition for details
// regarding the singular-value-decomposition of a matrix

int Rank(Matrix A)
{
    // The SVD routine in NEWMAT assume #rows >= #cols in A
    // if #rows < #cols, then we compute the SVD of the transpose of A
    if (A.nrows() >= A.ncols())
    {
        DiagonalMatrix D(A.ncols());
        SVD(A,D);
        int rank = 0;
        for (int i = 1; i <= A.ncols(); i++)
            if (abs(D(i)) > EPSILON)
                rank++;
        return (rank);
    }
    else {
        DiagonalMatrix D(A.nrows());
        SVD(A.t(),D);
        int rank = 0;
        for (int i = 1; i <= A.nrows(); i++)
            if (abs(D(i)) > EPSILON)
                rank++;
        return (rank);
    }
    
}

ColumnVector Find_Solution(Matrix A, ColumnVector y)
{
    // A should be of full rank and y is a column vector
    if (Rank(A) == min(A.ncols(), A.nrows()))
    {
        return ((A.t()*A).i())*A.t()*y;
    }
    else {
        cout << "Matrix: " << endl;
        cout << setw(9) << setprecision(3) << A;
        cout << "is not of full-rank... exiting..." << endl;
        exit (0);
    }
}

int main (int argc, char* argv[])
{
    Matrix A(2,4);
    
    A(1,1) = 1; A(1,2) = 2; A(1,3) = 1; A(1,4) =  0;
    A(2,1) = 4; A(2,2) = 3; A(2,3) = 0; A(2,4) =  1;
    
    ColumnVector y(2);
    y(1) = 6; y(2) = 12;
    
    cout << "Finding the BFSs for the LP example Section4 of Lesson 2" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Rank of A = " << Rank(A) << " (which has " << A.nrows();
    cout << " rows and " << A.ncols() << " cols)" << endl;
    cout << "So... we can drop two columns of A and preserve rank" << endl;
    
    // there are 4!/(2!*2!) = 6 choices of the cols to be dropped
    Matrix B1(2,2), B2(2,2), B3(2,2), B4(2,2), B5(2,2), B6(2,2);
    B1 = (A.column(1) | A.column(2));
    B2 = (A.column(1) | A.column(3));
    B3 = (A.column(1) | A.column(4));
    B4 = (A.column(2) | A.column(3));
    B5 = (A.column(2) | A.column(4));
    B6 = (A.column(3) | A.column(4));
    
    // I am not going to check the ranks of each of these 6 choices.  I have already
    // done it, and they are all of rank 2.  Therefore, each of them will give a BFS
    
    cout << "Apply Equation 1 of Lesson 2 to get four Basic Feasible Solutions" << endl << endl;
    
    ColumnVector s1(2), s2(2), s3(2), s4(2), s5(2), s6(2);
    s1 = Find_Solution(B1, y); s2 = Find_Solution(B2, y); s3 = Find_Solution(B3, y);
    s4 = Find_Solution(B4, y); s5 = Find_Solution(B5, y); s6 = Find_Solution(B6, y);
    
    ColumnVector soln1(4), soln2(4), soln3(4), soln4(4), soln5(4), soln6(4);
    soln1(1) = s1(1); soln1(2) = s1(2); soln1(3) = 0; soln1(4) = 0;
    soln2(1) = s2(1); soln2(2) = 0; soln2(3) = s2(2); soln2(4) = 0;
    soln3(1) = s3(1); soln3(2) = 0; soln3(3) = 0; soln3(4) = s3(2);
    soln4(1) = 0; soln4(2) = s4(1); soln4(3) = s4(2); soln4(4) = 0;
    soln5(1) = 0; soln5(2) = s5(1); soln5(3) = 0; soln5(4) = s5(2);
    soln6(1) = 0; soln6(2) = 0; soln6(3) = s6(1); soln6(4) = s6(2);
    
    {
        Matrix Collection_of_BFS(4,6);
        Collection_of_BFS = (soln1 | soln2 | soln3 | soln4 | soln5 | soln6);
        cout << "The Six Basic-Solutions are:" << endl;
        cout << setw(9) << setprecision(3) << Collection_of_BFS << endl;
        cout << "Verification:" << endl;
        cout << setw(9) << setprecision(3) << A*Collection_of_BFS << endl;
    }
    
    cout << "We have to eliminate the Basic-Solutions that are negative" << endl;
    {
        Matrix Collection_of_BFS(4,4);
        Collection_of_BFS = (soln1 | soln2 | soln5 | soln6);
        cout << "The Six Basic-Feasible-Solutions are:" << endl;
        cout << setw(9) << setprecision(3) << Collection_of_BFS << endl;
        
        
        cout << "We are maximizing 7*x1 + 5*x2; Therefore, for each BFS we have:" << endl;
        RowVector benefit(4);
        benefit(1) = 7; benefit(2) = 5; benefit(3) = 0; benefit(4) = 0;
        cout << setw(9) << setprecision(3) << benefit*Collection_of_BFS << endl;
        cout << "(Optimal) Largest value is 21; which comes from soln2" << endl;
        cout << "Optimizer is x1 = " << soln2(1) << "; x2 = " << soln2(2) << endl;
    }
}


