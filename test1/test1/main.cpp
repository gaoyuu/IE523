
#include <iostream>
#include <cmath>
using namespace std;


//intf(intn,intm)
//{
//if(n<10)
//return(m+1);
//else{
//m++;
//return(f(n/10,m));
//}
//}
//
int main(int argc,char*argv[])
{
    
    double **array=new double *[2];
    for(int i=0;i<2;i++)
        array[i]=new double[2];
    array[0][0]=2;array[0][1]=4;array[1][0]=6;array[1][1]=8;
    //cout<<array[0]<<endl;
    cout<<*(++array[0])<<endl;
    cout<<++(*array[0])<<endl;
    //cout<<array[0]<<endl;
    return(0);
}
//intx,y,*p,*q;
//p=&x;q=&y;x=35;y=46;*p=78;
//cout<<x<<""<<y<<endl;
//cout<<*p<<""<<*q<<endl;
//return(0);
//}

//intm=0;
//cout<<f(1234,m)<<endl;
//}

