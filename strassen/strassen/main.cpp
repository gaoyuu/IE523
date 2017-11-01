// (Tons of) Recursion in C++ illustration -- Strassen's Method of
// Matrix Multiplication
// Written by Prof. Sreenivas for IE523: Financial Computing and
// GE523: Intro to DEDS
// See Lesson 1 of my notes for the relevant details.

#include <iostream>
#include <cmath>

// This include file has the necessary template functions
#include "strassen.h"

using namespace std;

// In this main routine I am generating two random (2^k x 2^k) matrices, while
// k varies from 2 to 8 (i.e. two (2 x 2), (4 x 4), (8 x 8) ... (256 x 256) randomly
// generated matrices).  I compute the product of these two (randomly generated)
// matrices by Strassen's method and regular matrix multiplication. I present the
// cummulative errors between each member of the matrix as a measure of accurracy.

int main ()
{
    int my_index, k;
    double error = 0.0;
    
    srand( (unsigned)time( NULL ) );
    
    for (my_index = 1; my_index < 9; my_index++) {
        
        // creating the space for four matrices to be used for testing
        // if Strassen's method works
        k = (int) pow(2.0, (double) my_index);
        
        double **first_matrix = new double*[k];
        double **second_matrix = new double*[k];
        double **third_matrix = new double*[k];
        double **fourth_matrix = new double*[k];
        
        for (int i = 0; i < k; i++) {
            first_matrix[i] = new double[k];
            second_matrix[i] = new double[k];
            third_matrix[i] = new double[k];
            fourth_matrix[i] = new double[k];
        }
        
        // fill the first and second matrix with random entries
        create_random_matrix(first_matrix, k);
        create_random_matrix(second_matrix, k);
        
        third_matrix = strassen_multiply(first_matrix, second_matrix, my_index);
        
        fourth_matrix = regular_multiply(first_matrix, second_matrix, k);
        
        for (int j = 0; j < k; j++)
            for (int i = 0; i < k; i++)
                error += fabs(third_matrix[i][j] - fourth_matrix[i][j]);
        
        cout << "Matrix Size = (" << k << " x " << k << "); Absolute Error = " << error << endl;
        
        // free the space used up by the matrices
        delete [] first_matrix;
        delete [] second_matrix;
        delete [] third_matrix;
        delete [] fourth_matrix;
    }
    
}



