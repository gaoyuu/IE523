/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   /* time */
#include <iostream>
using namespace std;

int main ()
{
    int iSecret;
    
    /* initialize random seed: */
    srand( (unsigned int) time(NULL) );
    
    /* generate secret number between 1 and 10: */
    iSecret = rand() % 10 + 1;
    
    cout << iSecret << endl;
    return 0;
}
