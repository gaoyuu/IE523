//
//  main.cpp
//  Repeated_Squaring_AL
//
//  Created by Yu Gao on 10/31/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include "newmat.h"
#include "newmatap.h"

using namespace std;

class Repeated_Squaring_Instance
{
public:
    double get_uniform() {
        return (((double) random())/(pow(2.0, 31.0)-1.0));
    }
    
    Matrix create_random_matrix(int dimension){
        Matrix A(dimension, dimension);
        for (int i = 1; i <= dimension; i++) {
            for (int j = 1; j <= dimension; j++) {
                A(i,j) = 10.0 * get_uniform() - 5;
            }
        }
        return A;
    }
    
    Matrix repeated_squaring(Matrix A, int exponent, int dimension) {
        A(dimension,dimension);
        IdentityMatrix I(dimension);
        if (exponent == 0) {//exponent = 0
            return I;
        }
        else {
            if (exponent%2 == 1) // if exponent is odd
                return (A * repeated_squaring (A*A, (exponent-1)/2, dimension));
            else //if exponent is even
                return (A * repeated_squaring( A*A, exponent/2, dimension));
        }
    }
    
    Matrix direct_multiplication(Matrix A, int exponent,int dimension) {
        Matrix result(dimension,dimension);
        result = A;
        for (int i = 0; i < exponent; i++) {
            result = result * A;
        }
        return result;
    }
    
    float repeated_squaring_time(Matrix A, int exponent, int dimension) {
        clock_t time_before = clock();
        Matrix B = repeated_squaring(A, exponent, dimension);
        clock_t time_after = clock();
        float diff = ((float)time_after - (float)time_before);
        return diff/CLOCKS_PER_SEC;
    }
    
    float direct_multiplication_time(Matrix A, int exponent, int dimension) {
        clock_t time_before = clock();
        Matrix B = direct_multiplication(A, exponent, dimension);
        clock_t time_after = clock();
        float diff = ((float)time_after - (float)time_before);
        return diff/CLOCKS_PER_SEC;
    }
    
    void create_data_file(Matrix A, int dimension) {

        vector <float> repeated_time;
        vector <float> direct_time;
        for (int i = 0; i <= 300; i++) {
            repeated_time.push_back(repeated_squaring_time(A, i, dimension));
            direct_time.push_back(direct_multiplication_time(A, i, dimension));
        }

        ofstream simulated_file;
        ofstream theoretical_file;
        simulated_file.open("repeated_time");
        theoretical_file.open("direct_time");
        for (int i = 0; i <= repeated_time.size(); i++) {
            simulated_file << repeated_time[i] << endl;
            theoretical_file << direct_time[i] << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    Repeated_Squaring_Instance x;
    int dimension, exponent;
    sscanf (argv[1], "%d", &exponent);
    sscanf (argv[2], "%d", &dimension);
    
    cout << "The number of rows/colomns of the matrix is: " << dimension << endl;
    cout << "The exponent is: " << exponent << endl;
    
    Matrix A = x.create_random_matrix(dimension);
    
    cout << "Repeated Squaring Root Result:" << endl;
    float diff = x.repeated_squaring_time(A, exponent, dimension);
    cout << "It took " << diff << " seconds to complete" << endl;
    
    cout << "Direct Multiplication Result:" << endl;
    float diff_new = x.direct_multiplication_time(A, exponent, dimension);
    cout << "It took " << diff_new << " seconds to complete" << endl;
    
    x.create_data_file(A, dimension);
    
    return 0;
}
