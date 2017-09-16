#include <iostream>
#include <cmath>
using namespace std;


int main () {
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
    
    //each row
    //    for (int i = 1; i <= 9; i++)
    //    {
    //        for (int k = 1; k <= 9; k++)
    //        {
    //            for (int j = 1; j <= 9; j++)
    //            {
    //                double row[730];
    //                for (int k = 0; k < 730; k++)
    //                    row[k] = 0;
    //
    //                //for (int k = 1; k <= 9; k++)
    //                row[(81 * (i-1)) + k + (9 * (j-1))] = 1;
    
    
    //each column
    for (int j = 1; j <= 9; j++)
    {
        for (int k = 1; k <= 9; k++)
        {
            for (int i = 1; i <= 9; i++)
            {
                double row[730];
                for (int k = 0; k < 730; k++)
                    row[k] = 0;
                
                row[k + (9 * (j-1)) + (81 * (i-1))] = 1;
                for (int k = 0; k < 730; k++)
                    if (row[k] == 1)
                        cout << "(" << k << ":" <<row[k]<< ")";
                
            }
        }
    }
}
