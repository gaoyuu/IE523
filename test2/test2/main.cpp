#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;


int main(int argc , char* argv[])
{
    int num;
    cin >> num;
    int * p= NULL;
    p = (int *) malloc( sizeof(int) * num );
    memset(p, 0, sizeof(int) * num );
    int a;
    int i;
    for(i = 0;i < num;i++)
    {
        a = *(p+i);
        printf("a = %d\r\n",a);
    }
    free(p);
    return 0;
}
