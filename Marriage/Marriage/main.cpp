//
//  main.cpp
//  Marriage
//
//  Created by Yu Gao on 9/18/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

//
//  main.cpp
//  Stable Marriage Problem
//
//  Created by Ramavarapu Sreenivas on 8/29/14.
//  Copyright (c) 2014 Ramavarapu Sreenivas. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

class stable_marriage_instance
{
    // Private
    int no_of_couples;
    vector <vector <int> > Preference_of_men;
    vector <vector <int> > Preference_of_women;
    vector <int> match_for_men;
    vector <int> match_for_women;
    
    // private member function: checks if anybody is free in boolean "my_array"
    // returns the index of the first-person who is free in "my_array"
    // if no one is free it returns a -1.
    //[true,true,true,true]
    int anybody_free(vector <bool> my_array)
    {
        int i = 0;
        while(i < my_array.size()) {
            if (my_array[i] == true) {
                //cout << i;
                return i;
            } else {
                i++;
            }
        }
        //cout << -1;
        return -1;
        // fill the necessary code for this function
    }
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        // fill the necessary code for this function
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;

        int man_index, woman_index;

        // initializing everything
        for (int i= 0; i < no_of_couples; i++)
        {
            // do the necessary initialization here
        }

        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)
        {
            // fill the necessary code here
        }
    }
    
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        // reading the input filename from commandline
        ifstream input_filename(argv[1]);
        if (input_filename.is_open())
        {
            input_filename >> no_of_couples;
            //create colomns
            for (int i = 0; i < no_of_couples; i++)
            {
                vector <int> temp;
                Preference_of_men.push_back(temp);
                Preference_of_women.push_back(temp);
            }
            //read Men' preferences
            for (int i = 0; i < no_of_couples; i++)
            {
                for (int j = 0; j < no_of_couples; j++)
                {
                    int value_just_read;
                    input_filename >> value_just_read;
                    Preference_of_men[i].push_back(value_just_read);
                }
            }
            //read Women' preferences
            for (int i = 0; i < no_of_couples; i++)
            {
                for (int j = 0; j < no_of_couples; j++)
                {
                    int value_just_read;
                    input_filename >> value_just_read;
                    Preference_of_women[i].push_back(value_just_read);
                }
            }
            //print Men' preferences
            cout << "Gale Shapley Algorithm" << endl << "Input File Name: " << argv[1] << endl;
            cout << "number of Couples = " << no_of_couples << endl;
            cout << endl;
            cout << "Preferrences of Men" << endl;
            cout << "-----------------------";
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << endl << "(" << i << "): " ;
                for (int j = 0; j < no_of_couples; j++)
                    cout << Preference_of_men[i][j] << " ";
            }
            cout << endl << endl;
            //print Women' preferences
            cout << "Preferrences of Women" << endl;
            cout << "-----------------------";
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << endl << "(" << i << "): " ;
                for (int j = 0; j < no_of_couples; j++)
                    cout << Preference_of_women[i][j] << " ";
            }
            cout << endl << endl;
        } else {
            cout << "Input file missing" << endl;
            exit(0); }
    }
    
    // private member function: print solution
    void print_soln()
    {
        cout << "Matching of Men" << endl;
        for (int i = 0; i < match_for_men.size(); i++)
        {
            cout << endl << "Man :" << i << "-> Women: "<< match_for_men[i] ;
        }
        cout << endl << endl;
        
        cout << "Matching of Woman" << endl;
        for (int i = 0; i < match_for_women.size(); i++)
        {
            cout << endl << "Women :" << i << "-> Man: "<< match_for_women[i] ;
        }
        cout << endl << endl;
    }
    
public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);
        
//        Gale_Shapley();
        
        print_soln();
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}
