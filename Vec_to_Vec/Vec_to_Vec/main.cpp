//
//  main.cpp
//  Vec_to_Vec
//
//  Created by Yu Gao on 9/24/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//


#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char * const argv[]) {
    
    vector <vector <int> > test;
    
    int m, n;
    
    cout << "#Rows? ";
    cin >> m;
    cout << "#Cols? ";
    cin >> n;
    
    // we want to "stack" n-many m-dimensional vectors
    // to create an m-row n-col array.
    
    for (int i = 0; i < n; i++)
    {
        vector <int> temp;
        test.push_back(temp);
    }
    
    // get the array values from the user
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int value;
            cout << "array[" << j << "][" << i << "] = ";
            cin >> value;
            test[i].push_back(value);
        }
    }
    
    int a = 1;
    // print array
    for (int i = 0; i < m; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
        {   cout << test[j][i] <<"("<<a<<") ";
            a++;
        }
    }
    cout << endl;
    
    return 0;
}
