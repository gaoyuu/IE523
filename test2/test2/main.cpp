//Generating random variates from arbitrary distributions using the
//inverse transform method.I am generating exponentially distributed
//variables here. Written by Prof.Sreenivas for IE523:Financial Computing
#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<cstdlib>
using namespace std;

float get_uniform()
{
    return(((float)random())/(pow(2.0,31.0) - 1.0));
}

float get_exp(float lambda)
{
    return((- 1.0/lambda) * log(1.0 - get_uniform()));
}
int main(int argc,char*argv[])
{
    float lambda,y;
    int no_of_trials,count[100];
    sscanf(argv[1],"%f",&lambda);
    sscanf(argv[2],"%d",&no_of_trials);
    ofstream outf(argv[3]);
    for(int i=0;i<100;i++)
        count[i]=0;
    for(int i=0;i<no_of_trials;i++){
        y=get_exp(lambda);
        for(int j=0;j <100;j++)
            if(y<((float) j/10))
                count[j]++;
    }
    for(int j=0;j<100;j++)
        outf<<((float) j/10)<<","<<
        ((float)count[j])/((float)no_of_trials)<<","<<(1.0 - exp(- 1.0*lambda*((float)j/10)))<<endl;
}
