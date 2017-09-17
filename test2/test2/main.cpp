#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

double solution[729];



void read_input_data(char* argv[])
{
    // reading the input filename from commandline
    ifstream input_filename(argv[1]);
    
    if (input_filename.is_open()) {
        
        cout << "Input File Name: " << argv[1] << endl;
        cout << endl << "Initial Board Position" << endl;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                int value_just_read;
                input_filename >> value_just_read;
                
                // check if we have a legitimate integer between 1 and 9
                if ((value_just_read >= 1) && (value_just_read <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    cout << value_just_read << " ";
                    
                    solution[(81 * (i - 1)) + 9 * (j - 1) + value_just_read ] = 1;
                    // add appropriate constraints that bind the value of the
                    // appropriate variables based on the incomplete information
                    // that was read from the input file
                    
                    
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    cout << "X ";
                }
                
            }
            cout << endl;
        }
    }
    else {
        cout << "Input file missing" << endl;
        exit(0);
    }
}

int main (int argc, char* argv[]){
    //each entry
    //    for (int i = 1; i <= 9; i++)
    //    {
    //        for (int j = 1; j <= 9; j++)
    //        {
    //
    //            double row[730];
    //            for (int k = 0; k < 730; k++)
    //                row[k] = 0;
    //
    //            for (int k = 1; k <= 9; k++)
    //                row[(81*(i-1)) + (9*(j-1)) + k] = 1;
    
    
    //    //each row
    //            for (int i = 1; i <= 9; i++)
    //            {
    //                for (int k = 1; k <= 9; k++)
    //                {
    //    //                for (int j = 1; j <= 9; j++)
    //    //                {
    //                        double row[730];
    //                        for (int k = 0; k < 730; k++)
    //                            row[k] = 0;
    //
    //                    for (int j = 1; j <= 9; j++)
    //                    {
    //
    //                        row[(81 * (i-1)) + k + (9 * (j-1))] = 1;
    //
    //
    //                    }
    //
    //                    for (int k = 0; k < 730; k++)
    //                        if (row[k] == 1)
    //                            cout << "(" << k << ":" <<row[k]<< ")";
    //                    cout << endl;
    //                }
    //            }
    //        }
    
    
    
    //    //each column
    //    for (int j = 1; j <= 9; j++)
    //    {
    //        for (int k = 1; k <= 9; k++)
    //        {
    //            for (int i = 1; i <= 9; i++)
    //            {
    //                double row[730];
    //                for (int k = 0; k < 730; k++)
    //                    row[k] = 0;
    //
    //                row[k + (9 * (j-1)) + (81 * (i-1))] = 1;
    //
    //                for (int k = 0; k < 730; k++)
    //                    if (row[k] == 1)
    //                        cout << "(" << k << ":" <<row[k]<< ")";
    //            }
    //            cout << endl;
    //        }
    //    }
    //}
    
            for (int k = 1; k <= 9; k++)
            {
                for (int j = 1; j <= 9; j++)
                {
                    double row[730];
                    for (int k = 0; k < 730; k++)
                        row[k] = 0;
                    if ((j % 3) == 0)
                    {
                        row[k + (9 * 2) + (81 * ((j-1) / 3))] = 1;
                    }
                    else
                    {
                        row[k + (9 * ((j % 3) -1)) + (81 * ((j-1) / 3))] = 1;
                    }
    
                    for (int k = 0; k < 730; k++)
                        if (row[k] == 1)
                            cout << "(" << k << ":" <<row[k]<< ")";
                }
                cout<<endl;
            }
        }

//    {
//        for (int k = 1; k <= 9; k++)
//        {
//            double row[730];
//            for (int i = 0; i < 730; i++)
//                row[i]=0;
//            
//            for (int i = 1 ; i <= 3; i++)
//                for (int j = 1; j <= 3; j++)
//                    row[(81 * (i-1)) + (9 *(j - 1)) + k] = 1;
//            
//            for (int k = 0; k < 730; k++)
//                if (row[k] == 1)
//                    cout << "(" << k << ":" <<row[k]<< ")";
//            cout<<endl;
//        }
//        
//    }
//}


//    for (int k = 1; k <= 9; k++)
//    {
//        for (int j = 1; j <= 9; j++)
//        {
//            double row[730];
//            for (int k = 0; k < 730; k++)
//                row[k] = 0;
//            if ((j % 3) == 0)
//            {
//                row[297 + k + (9 * 2) + (81 * ((j-1) / 3))] = 1;
//            }
//            else
//            {
//                row[297 + k + (9 * ((j % 3) -1)) + (81 * ((j-1) / 3))] = 1;
//            }
//
//
//            for (int k = 0; k < 730; k++)
//                if (row[k] == 1)
//                    cout << "(" << k << ":" <<row[k]<< ")";
//
//
//        }
//        cout << endl;
//    }
//read_input_data(argv);
//
//    for (int k = 0; k < 730; k++)
//        if (solution[k] == 1)
//        cout << k << " ";
//
//return (0);
//}
