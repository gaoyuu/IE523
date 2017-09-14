#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include "lp_lib.h"

using namespace std;

int main (int argc, char* argv[])
{
    
    lprec *lp;
    REAL solution[2];
    
    // setting the problem up: 2 constraints
    lp = make_lp(2,0);
    
    // This keeps the message reporting of lp_solve to a minimum
    set_verbose(lp, 3);
    
    // first constraint x1 + 2x2 <= 6
    // second constraint 4x1 + 3x2 <= 12
    // objective function 7x1+5x2...
    // the 0-th value of each column is the objective function for
    // that column
    
    // first column
    {
        double col[] = {-7, 1, 4};
        add_column(lp, col);
    }
    // second column
    {
        double col[] = {-5, 2, 3};
        add_column(lp, col);
    }
    // RHS vector -- 0th value is ignored
    {
        double rhs[] = {0, 6, 12};
        set_rh_vec(lp, rhs);
    }
    
    // set the constraint type for each row
    set_constr_type(lp, 1, LE);
    set_constr_type(lp, 2, LE);
    
    // print lp
    print_lp(lp);
    
    // solve the lp
    solve(lp);
    
    // print optimal value
    cout << "Optimal Value is: " << -1*get_objective(lp) << endl;
    
    // print the optimizing values of the variables
    get_variables(lp, solution);
    cout << "Optimal solution:" << endl;
    for (int i = 0; i < 2; i++)
        cout << "x[" << i+1 << "] = " << solution[i] << endl;
    
    // delete the lp to release memory
    delete_lp(lp);
    
    return(0);
}
