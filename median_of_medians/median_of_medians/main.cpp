// The median-of-medians algorithm for Deterministic Selection of the
// the k-th smallest member in a list.
// Written by Prof. Sreenivas (rsree@illinois.edu)
// For IE523: Financial Computing

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// cf http://www.cplusplus.com/reference/random/uniform_real_distribution/operator()/
// If you want to set a seed -- do it only after debug phase is completed
// otherwise errors will not be repeatable.
// unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
//default_random_engine generator (seed);

default_random_engine generator;

double get_uniform()
{
    std::uniform_real_distribution <double> distribution(0.0,1.0);
    double number = distribution(generator);
    return (number);
}

double get_standard_cauchy()
{
    return tan(-1.570796327 + (get_uniform()*3.141592654));
}

double selection_from_bubble_sort(vector <double> & list, long k)
{
    int flag = 1;
    float temp;
    for (int i = 1; (i <= list.size()) && flag; i++) {
        flag = 0;
        for (int j = 0; j < (list.size()-1); j++)
            if (list[j+1] < list[j]) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
                flag = 1;
            }
    }
    // list[] is now sorted.   Pick the k-th element from the sorted list
    // since the index starts from 0, we are looking for the (k-1)-th element
    return (list[k-1]);
}

double selection_from_quick_sort(vector <double> & list, long k)
{
    sort(list.begin(), list.end());
    // list[] is now sorted.   Pick the k-th element from the sorted list
    // since the index starts from 0, we are looking for the (k-1)-th element
    return (list[k-1]);
}

double deterministic_selection(vector <double> & list, long k)
{
    double median_of_medians;
    vector <double> list_of_medians;
    
    if (list.size() <= 5)
        return (selection_from_bubble_sort(list, k));
    else {
        for (int i = 0; i < list.size(); i = i + 5) {
            vector <double> five_element_long_segment;
            five_element_long_segment.push_back(list[i]);
            if ( (i+1) < list.size())
                five_element_long_segment.push_back(list[i+1]);
            if ( (i+2) < list.size())
                five_element_long_segment.push_back(list[i+2]);
            if ( (i+3) < list.size())
                five_element_long_segment.push_back(list[i+3]);
            if ( (i+4) < list.size())
                five_element_long_segment.push_back(list[i+4]);
            // pick the median of the five-element list (note, it might not have exactly
            // 5 elements all the time).  The following switch-case options consider all
            // possible definitions of the median depending on the #elements in the vector
            switch (five_element_long_segment.size()) {
                case 5:
                    list_of_medians.push_back(deterministic_selection(five_element_long_segment, 3));
                    break;
                case 4:
                    list_of_medians.push_back((deterministic_selection(five_element_long_segment,2) +
                                               deterministic_selection(five_element_long_segment,3))/2.0);
                    break;
                case 3:
                    list_of_medians.push_back(deterministic_selection(five_element_long_segment, 2));
                    break;
                case 2:
                    list_of_medians.push_back((five_element_long_segment[0]+five_element_long_segment[1])/2.0);
                    break;
                default:
                    list_of_medians.push_back(five_element_long_segment[0]);
                    break;
            }
        }
        
        if (list_of_medians.size()%2 == 1) // list-size is odd, so pick the "middle" element
            median_of_medians = deterministic_selection(list_of_medians, ((list_of_medians.size()-1)/2) + 1);
        else // list-size is even, so pick the average value of the two "middle" elements
            median_of_medians =
            (deterministic_selection(list_of_medians, (list_of_medians.size())/2) +
             (deterministic_selection(list_of_medians, ((list_of_medians.size())/2) + 1)))/2.0;
        
        // split list into three lists called: less_than_median_of_medians, equal_to_median_of_medians, and
        // greater-than-median_of_medians
        vector <double> less_than_median_of_medians;
        vector <double> equal_to_median_of_medians;
        vector <double> greater_than_median_of_medians;
        for (int i = 0; i < list.size(); i++) {
            if (list[i] < median_of_medians)
                less_than_median_of_medians.push_back(list[i]);
            if (list[i] == median_of_medians)
                equal_to_median_of_medians.push_back(list[i]);
            if (list[i] > median_of_medians)
                greater_than_median_of_medians.push_back(list[i]);
        }
        if (k <= less_than_median_of_medians.size())
            return (deterministic_selection(less_than_median_of_medians, k));
        else if (k > (less_than_median_of_medians.size() + equal_to_median_of_medians.size()) )
            return (deterministic_selection(greater_than_median_of_medians, (k - less_than_median_of_medians.size() - equal_to_median_of_medians.size())));
        else
            return (median_of_medians);
    }
}


int main (int argc, char* argv[])
{
    int no_of_trials;
    clock_t time_before, time_after;
    float diff;
    
    sscanf (argv[1], "%d", &no_of_trials);
    
    vector <double> my_list;
    vector <double> copy_of_my_list;
    for (int i = 0; i < no_of_trials; i++) {
        double x = get_standard_cauchy();
        my_list.push_back(x);
        copy_of_my_list.push_back(x);
    }
    
    cout << "Number of trials = " << no_of_trials << endl;
    cout << "-------------" << endl;
    cout << "Deterministic Selection Based Method" << endl;
    time_before = clock(); // recording time before Deterministic Selection algorithm starts
    cout << "The (" << my_list.size()/2 + 1 << ")-th smallest element in a " <<
    my_list.size() << "-long list is " << deterministic_selection (my_list, my_list.size()/2 + 1) << endl;
    time_after = clock(); // recording time after Deterministic Selection algorithm finishes
    diff = ((float) time_after - (float) time_before);
    cout << "It took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;
    
    cout << "-------------" << endl;
    cout << "Bubble Sort Based Method" << endl;
    time_before = clock(); // recording time before bubble sort starts
    cout << "The (" << my_list.size()/2 + 1 << ")-th smallest element in a " <<
    my_list.size() << "-long list is " << selection_from_bubble_sort(my_list, my_list.size()/2 + 1) << endl;
    time_after = clock(); // recording time after bubble sort finishes
    diff = ((float) time_after - (float) time_before);
    cout << "It took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;
    
    cout << "-------------" << endl;
    cout << "Quick Sort Based Method" << endl;
    time_before = clock(); // recording time before bubble sort starts
    cout << "The (" << copy_of_my_list.size()/2 + 1 << ")-th smallest element in a ";
    cout << copy_of_my_list.size() << "-long list is " << selection_from_quick_sort(copy_of_my_list, copy_of_my_list.size()/2 + 1) << endl;
    time_after = clock(); // recording time after bubble sort finishes
    diff = ((float) time_after - (float) time_before);
    cout << "It took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;
    cout << "-------------" << endl;
}

