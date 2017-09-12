#include <iostream>
#include <cmath>
using namespace std;



void f()
{
    char c;
    cin.get(c);//thislinereadscharacter”c”
    if('\n' ==c)//’\n’is”return/newline”char
        return;
    //cout<<c;
    f();
    cout<<c;
}

int main()
{
    
    f();
    cout<<endl;
}
