#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool rank_check (vector <int> my_array, int index1, int index2)
{
    bool result = true;
    for (int i = 0; i < my_array.size(); i++)
    {
        if (my_array[i] == index1)
        {
            cout << "true";
            result = true;
            break;
        }
        if (my_array[i] == index2)
        {
            cout << "false";
            result = false;
            break;
        }
        
    }
    return result;
}

int main(int argc, const char * argv[])
{
    vector <int> my_array;
    my_array.push_back(0);
    my_array.push_back(1);
    my_array.push_back(2);
    my_array.push_back(3);
    //    my_array.push_back(true);
    //    my_array.push_back(true);
    //    my_array.push_back(true);
    //    my_array.push_back(true);
    my_array.push_back(4);
    
    //anybody_free(my_array);
    rank_check(my_array, 4, 3);
    
    
    
}

//int anybody_free(vector <bool> my_array)
//{
//    int i = 0;
//    while(i < my_array.size()) {
//        if (my_array[i] == true) {
//            cout << i;
//            return i;
////            break;
//        } else {
//            i++;
//        }
//    }
//    cout << -1;
//    return -1;
//    // fill the necessary code for this function
//}
//
//
//
//int main(int argc, const char * argv[])
//{
//    vector <bool> my_array;
//    my_array.push_back(false);
//    my_array.push_back(false);
//    my_array.push_back(false);
//    my_array.push_back(false);
////    my_array.push_back(true);
////    my_array.push_back(true);
////    my_array.push_back(true);
////    my_array.push_back(true);
//    my_array.push_back(false);
//
//    anybody_free(my_array);
//
//
//}

