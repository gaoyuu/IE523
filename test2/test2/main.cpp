#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int anybody_free(vector <bool> my_array)
{
    int i = 0;
    while(i < my_array.size()) {
        if (my_array[i] == true) {
            cout << i;
            return i;
//            break;
        } else {
            i++;
        }
    }
    cout << -1;
    return -1;
    // fill the necessary code for this function
}



int main(int argc, const char * argv[])
{
    vector <bool> my_array;
    my_array.push_back(false);
    my_array.push_back(false);
    my_array.push_back(false);
    my_array.push_back(false);
//    my_array.push_back(true);
//    my_array.push_back(true);
//    my_array.push_back(true);
//    my_array.push_back(true);
    my_array.push_back(false);
    
    anybody_free(my_array);
    
    
}
