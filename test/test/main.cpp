// Dynamic Arrays in C++
// Prof. R.S. Sreenivas
// MSFE C++ bootcamp

// Dynamic Arrays in C++
// Prof. R.S. Sreenivas
// MSFE C++ bootcamp

#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
    int n, m;
    
    cout << "#Rows? ";
    cin >> n;
    cout << "#Cols? ";
    cin >> m;
    
    // Xcode for Macs will let you do something like double array[n][n]
    // where the size of the array is a variable.  Visual Studio will
    // squawk at it, though... the correct way of doing it is via the
    // Pointers-to-pointers method, shown below
    double **array = new double*[n];
    
    for (int i = 0; i < n; i++)
        array[i] = new double[m];
    
    
    cout << "Value of array = " << array << endl;
    cout << "Content of array = " << *array << endl;
    for (int i = 0; i < n; i++)
        cout << "Value of array[" << i << "] = " << array[i] << endl;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cout << "Type value of array[" << i << "][" << j << "]: ";
            cin >> array[i][j];
        }
    
    // printing the array
    cout << "Printing the array" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << array[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    
    
    for (int i = 0; i < n; i++)
        cout << "Content of array[" << i << "] = " << *(++(++array[i])) <<endl;
    
    
    return (0);
}


