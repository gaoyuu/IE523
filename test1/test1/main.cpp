
#include <iostream>
#include <cmath>
using namespace std;


int take(int n, int i)
{
    // write a **RECURSIVE** implementation of n-take-i.
    // If you made it non-recurisive (i.e. n!/((n-i)!i!)) -- it
    // will take too long for large sizes
    if (i == 0) {
        return 1;
    } else {
        return (n * take(n - 1, i - 1)) / i;
    }
    
}

int main(int argc,char*argv[])
{
    cout << take(7,3) << endl;
}

