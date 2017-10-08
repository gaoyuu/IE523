// Illustration of concepts from Linear Algebra using the NEWMAT library
// Written by Prof. R.S. Sreenivas for IE523: Financial Computation
// We want to check if there is (or, if there is no) solution to Ax = y
// Notice, in my example A is singular, and therefore has no inverse.

#include <iostream>
#include <iomanip>
#include <cmath>
#include "/Users/gaoyu/Documents/Courses/newmat11/newmatap.h"
#include "/Users/gaoyu/Documents/Courses/newmat11/newmat.h"
#include "/Users/gaoyu/Documents/Courses/newmat11/newmatio.h"

using namespace std;

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

ColumnVector Find_Solution(Matrix A, Matrix y)
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
    Matrix A(4,4);
    
    A(1,1) = 1; A(1,2) =  1; A(1,3) =  1; A(1,4) =  4;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = -1; A(2,4) =  0;
    A(3,1) = 1; A(3,2) = -1; A(3,3) =  1; A(3,4) =  6;
    A(4,1) = 1; A(4,2) =  1; A(4,3) = -1; A(4,4) = -2;
    
    Matrix y(4,1);
    y(1,1) = -4; y(2,1) = 6; y(3,1) = 0; y(4,1) = 2;
    
    cout << "Finding the general solution to Ax = b in Lesson 2" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Rank of A = " << Rank(A) << " (which has " << A.nrows();
    cout << " rows and " << A.ncols() << " cols)" << endl;
    cout << "So... we can drop one column of A preserve rank" << endl;
    
    // select first three cols of A
    Matrix B1(4,3), B2(4,3), B3(4,3), B4(4,3);
    B1 = (A.column(1) | A.column(2) | A.column(3));
    B2 = (A.column(1) | A.column(2) | A.column(4));
    B3 = (A.column(1) | A.column(3) | A.column(4));
    B4 = (A.column(2) | A.column(3) | A.column(4));
    
    cout << "Ranks of:" << endl;
    cout << "(c1 c2 c3) = " << Rank(B1) << "; (c1 c2 c4) = " << Rank(B2);
    cout << "; (c1 c3 c4) = " << Rank(B3) << "; (c2 c3 c4) = " << Rank(B4) << endl;
    cout << "Apply Equation 1 of Lesson 2 to get four Basic Feasible Solutions" << endl << endl;
    
    ColumnVector s1(3), s2(3), s3(3), s4(3);
    s1 = Find_Solution(B1, y); s2 = Find_Solution(B2, y);
    s3 = Find_Solution(B3, y); s4 = Find_Solution(B4, y);
    
    ColumnVector soln1(4), soln2(4), soln3(4), soln4(4);
    soln1(1) = s1(1); soln1(2) = s1(2); soln1(3) = s1(3); soln1(4) = 0;
    soln2(1) = s2(1); soln2(2) = s2(2); soln2(3) = 0; soln2(4) = s2(3);
    soln3(1) = s3(1); soln3(2) = 0; soln3(3) = s3(2); soln3(4) = s3(3);
    soln4(1) = 0; soln4(2) = s4(1); soln4(3) = s4(2); soln4(4) = s4(3);
    
    Matrix Collection_of_BFS(4,4);
    Collection_of_BFS = (soln1 | soln2 | soln3 | soln4);
    cout << "The Four Basic-Feasible-Solutions are:" << endl;
    cout << setw(9) << setprecision(3) << Collection_of_BFS << endl;
    cout << "Verification:" << endl;
    cout << setw(9) << setprecision(3) << A*Collection_of_BFS << endl;
    
    cout << "Rank of [soln1 | soln2 | soln3 | soln4] is: " << Rank(Collection_of_BFS);
    cout << ". So, we only need two of these four" << endl;
    Matrix BFS_subset(4,2);
    BFS_subset = (soln1 | soln2);
    cout << "Rank of [soln1 | soln2] is: " << Rank(BFS_subset);
    cout << ". So, soln1 and soln2 are sufficient." << endl;
    cout << "--------------------------------------------------" << endl;
    
    // express soln3 in terms of soln1 and soln2
    ColumnVector x(2);
    x = Find_Solution(BFS_subset, soln3);
    cout << "soln3 = (" << x(1) << " * soln1) + (" << x(2) << " * soln2)" << endl;
    x = Find_Solution(BFS_subset, soln4);
    cout << "soln4 = (" << x(1) << " * soln1) + (" << x(2) << " * soln2)" << endl;
}


