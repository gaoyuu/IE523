//
//  main.cpp
//  linear_algebra1
//
//  Created by Yu Gao on 10/8/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

// Illustration of concepts from Linear Algebra using the NEWMAT library
// Written by Prof. R.S. Sreenivas for IE523: Financial Computation
// We want to check if there is (or, if there is no) solution to Ax = y
// Notice, in my example A is singular, and therefore has no inverse.

#include <iostream>
#include <iomanip>
#include <cmath>
#include "/Users/gaoyu/Documents/Courses/newmat10/newmatap.h"
#include "/Users/gaoyu/Documents/Courses/newmat10/newmat.h"
#include "/Users/gaoyu/Documents/Courses/newmat10/newmatio.h"
using namespace std;

#define EPSILON 0.0000001

// This routine computes the rank of a matrix by counting the number of
// non-zero singular-values of the matrix.
// See http://en.wikipedia.org/wiki/Singular_value_decomposition for details
// regarding the singular-value-decomposition of a matrix

int Rank(Matrix A, int no_of_rows_of_A, int no_of_cols_of_A)
{
    // The SVD routine in NEWMAT assume #rows >= #cols in A
    // if #rows < #cols, then we compute the SVD of the transpose of A
    if (no_of_rows_of_A >= no_of_cols_of_A)
    {
        DiagonalMatrix D(no_of_cols_of_A);
        SVD(A,D);
        int rank = 0;
        for (int i = 1; i <= no_of_cols_of_A; i++)
            if (abs(D(i)) > EPSILON)
                rank++;
        return (rank);
    }
    else {
        DiagonalMatrix D(no_of_rows_of_A);
        SVD(A.t(),D);
        int rank = 0;
        for (int i = 1; i <= no_of_rows_of_A; i++)
            if (abs(D(i)) > EPSILON)
                rank++;
        return (rank);
    }
    
}

int main (int argc, char* argv[])
{
    Matrix A(4,4);
    
    A(1,1) = 1; A(1,2) =  1; A(1,3) =  1; A(1,4) =  4;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = -1; A(2,4) =  0;
    A(3,1) = 1; A(3,2) = -1; A(3,3) =  1; A(3,4) =  6;
    A(4,1) = 1; A(4,2) =  1; A(4,3) = -1; A(4,4) = -2;
    
    Matrix y(4,1);
    y(1,1) = -4; y(2,1) = 6; y(3,1) = 0; y(4,1) = 2;
    
    cout << "Illustration of concepts from Linear Algebra & NEWMAT" << endl;
    cout << "A matrix:" << endl;
    cout << setw(9) << setprecision(3) << A;
    cout << "y vector:" << endl;
    cout << setw(9) << setprecision(3) << y << endl;
    
    cout << "The determinant of A = " << A.Determinant() << endl;
    if (abs(A.Determinant()) < EPSILON)
        cout << "Matrix A does not have an inverse" << endl;
    else {
        cout << "Matrix A has an inverse" << endl;
    }
    
    cout << "Rank of A = " << Rank(A, 4, 4) << endl;
    
    Matrix B(4,5);
    B = (A | y);
    
    cout << endl << "(A | y) Matrix:" << endl;
    cout << setw(9) << setprecision(3) << B << endl;
    cout << "Rank of (A | y) = " << Rank(B, 4, 5) << endl;
    
    if (Rank(A, 4, 4) == Rank(B, 4, 5))
        cout << "There is a solution to Ax = y" << endl;
    else
        cout << "There is no solution to Ax = y" << endl;
    
    cout << "---------------------------------" << endl;
    y(1,1) = 1; y(2,1) = 0; y(3,1) = 0; y(4,1) = 0;
    cout << "New value for y vector:" << endl;
    cout << setw(9) << setprecision(3) << y << endl;
    
    B = (A | y);
    
    cout << "(A | y) Matrix:" << endl;
    cout << setw(9) << setprecision(3) << B << endl;
    cout << "Rank of (A | y) = " << Rank(B, 4, 5) << endl;
    
    if (Rank(A, 4, 4) == Rank(B, 4, 5))
        cout << "There is a solution to Ax = y" << endl;
    else
        cout << "There is no solution to Ax = y" << endl;
    cout << "---------------------------------" << endl;
}


