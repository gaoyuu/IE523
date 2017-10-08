// Illustration of how to read numbers from a file
// Written by Prof. Sreenivas for IE523: Financial Computing

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#include "lp_lib.h"

using namespace std;

const double ERROR = 1e-10;
int number_of_cash_flows;
vector <double> price_list;
vector <int> maturity_list;
vector <double> yield_to_maturity;
vector <double> duration;
vector <double> convexity;
double debt_obligation_amount;
double time_when_debt_is_due;
vector <double> percentage_of_cash_flow_to_meet_debt_obligation;

double my_function(vector <double> cash_flow, double price, int maturity, double rate)
{
    double result = price * pow((1+rate), (double) maturity);
    for (int i = 0; i < maturity; i++)
        result -= (cash_flow[i] * pow((1+rate), (double) (maturity - 1 - i)));
    return (result);
}

double derivative_function(vector <double> cash_flow, double price, int maturity, double rate)
{
    double result = ((double) maturity) * price * pow((1+rate), (double) maturity-1);
    for (int i = 0; i < maturity-1; i++)
        result -= ((maturity - 1 - i) * cash_flow[i] * pow((1+rate), (double) (maturity-2-i)));
    return (result);
}

double Newton_Raphson(vector <double> cash_flow, double price, int maturity, double rate)
{
    while (abs(my_function(cash_flow, price, maturity, rate)) > ERROR) {
        rate -= my_function(cash_flow, price, maturity, rate)/derivative_function(cash_flow, price, maturity, rate);
    }
    return (rate);
}

double get_duration(vector <double> cash_flow, double price, int maturity, double rate)
{
    double duration = 0.0;
    for (int i = 0; i < maturity; i++)
        duration += (cash_flow[i]*((double) i+1)/pow((1+rate), (double) i+1));
    duration = duration/price;
    return (duration);
}

double get_convexity(vector <double> cash_flow, double price, int maturity, double rate)
{
    double convexity = 0.0;
    for (int i = 0; i < maturity; i++)
        convexity += (cash_flow[i]*((double) (i+1)*(i+2))/pow((1+rate), (double) i+3));
    convexity = convexity/price;
    return (convexity);
}

double present_value_of_debt()
{
    double average_rate = 0;
    for (int i = 0; i < number_of_cash_flows; i++)
    {
        average_rate += yield_to_maturity[i];
    }
    average_rate = average_rate/((double) number_of_cash_flows);
    return (debt_obligation_amount/(pow((1+average_rate), (double) time_when_debt_is_due)));
}

void print_data(char *filename)
{
    cout << "Input File: " << filename << endl;
    cout << "We owe " << debt_obligation_amount << " in " << time_when_debt_is_due << " years" << endl;
    cout << "Number of Cash Flows: " << number_of_cash_flows << endl;
    for (int i = 0; i < number_of_cash_flows; i++)
    {
        cout << "------------------------------------------------------------------" << endl;
        cout << "Cash Flow #" << i+1 << endl;
        cout << "Price = " << price_list[i] << endl;
        cout << "Maturity = " << maturity_list[i] << endl;
        cout << "Yield to Maturity = " << yield_to_maturity[i] << endl;
        cout << "Duration = " << duration[i] << endl;
        cout << "Convexity = " << convexity[i] << endl;
        cout << "Percentage of Face Value that would meet the obligation = " <<
        percentage_of_cash_flow_to_meet_debt_obligation[i] << endl;
    }
    cout << "******************************************************************" << endl;
    double average_rate = 0;
    for (int i = 0; i < number_of_cash_flows; i++)
    {
        average_rate += yield_to_maturity[i];
    }
    average_rate = average_rate/((double) number_of_cash_flows);
    cout << "Average YTM (which I use to compute PV of Debt) = " << average_rate << endl;
    cout << "Present value of debt = " << present_value_of_debt() << endl;
    cout << "******************************************************************" << endl;
}

void get_data(char* argv[])
{
    // First command line input is the name of the input file
    ifstream input_file(argv[1]);
    
    if (input_file.is_open()) // If the input file exists in the local directory
    {
        input_file >> number_of_cash_flows; // read the number_cash_flows
        
        for (int i = 0; i < number_of_cash_flows; i++)
        {
            vector <double> cash_flow; //declare a vector for cash flow
            double value_just_read_from_file;
            double price;
            int maturity;
            
            input_file >> price; // read the price
            price_list.push_back(price);
            
            input_file >> maturity;  // read the maturity
            maturity_list.push_back(maturity);
            
            // read the cash flows
            for (int j = 0; j < maturity; j++)
            {
                input_file >> value_just_read_from_file;
                cash_flow.push_back(value_just_read_from_file);
            }
            
            // get the yield to maturity for the cash flow
            double r = Newton_Raphson(cash_flow, price, maturity, 0.0);
            yield_to_maturity.push_back(r);
            
            // get duration of the cash flow
            double d = get_duration(cash_flow, price, maturity, r);
            duration.push_back(d);
            
            // get convexity of the cash flow
            double c = get_convexity(cash_flow, price, maturity, r);
            convexity.push_back(c);
        }
        
        // read the information about the debt obligation
        input_file >> debt_obligation_amount;
        input_file >> time_when_debt_is_due;
        
        // computing the %age of cash flow we need to buy to satisfy
        // the future debt obligation
        for (int i = 0; i < number_of_cash_flows; i++)
        {
            //double pv_of_debt_wrt_current_cash_flow = debt_obligation_amount/
            //pow((1+yield_to_maturity[i]), (double) time_when_debt_is_due);
            //percentage_of_cash_flow_to_meet_debt_obligation.push_back(pv_of_debt_wrt_current_cash_flow/price_list[i]);
            percentage_of_cash_flow_to_meet_debt_obligation.push_back(present_value_of_debt()/price_list[i]);
        }
    }
    else {
        // I need all this stuff to print out the name of the PWD
        char *path=NULL;
        size_t size = 0;
        path = getcwd(path, size);
        cout << "Input file: " << argv[1] << " does not exist in " << path << endl;
        exit(1);
    }
}

void get_optimal_portfolio()
{
    lprec *lp;
    REAL solution[number_of_cash_flows];
    
    lp = make_lp(0,number_of_cash_flows);
    
    // This keeps the message reporting of lp_solve to a minimum
    set_verbose(lp, 3);
    
    // all %ages of cash flows must add to 1 constraint
    //{
    //    REAL row[number_of_cash_flows+1];
    //    for (int a = 0; a <= number_of_cash_flows; a++)
    //        if (0 == a)
    //            row[a] = 0.0;
    //        else
    //            row[a] = 1.0;
    //    add_constraint(lp, row, EQ, 1);
    //}
    // Match PVs
    {
        REAL row[number_of_cash_flows+1];
        row[0] = 0;
        for (int a = 1; a <= number_of_cash_flows; a++)
            row[a] = price_list[a-1];
        add_constraint(lp, row, EQ, present_value_of_debt());
    }
    // duration constraint
    {
        REAL row[number_of_cash_flows+1];
        for (int a = 0; a <= number_of_cash_flows; a++)
            if (0 == a)
                row[a] = 0.0;
            else
                row[a] = duration[a-1]*(price_list[a-1])/present_value_of_debt();
        add_constraint(lp, row, EQ, time_when_debt_is_due);
    }
    // objective: maximize convexity of portfolio
    // since lpsolve minimizes the cost function, I have
    // to multiply the objective function by -1 to get
    // it maximize the objective
    {
        REAL row[number_of_cash_flows+1];
        for (int a = 0; a <= number_of_cash_flows; a++)
            if (0 == a)
                row[a] = 0.0;
            else
                row[a] = -1.0*convexity[a-1]*(price_list[a-1]/present_value_of_debt());
        set_obj_fn(lp, row);
    }
    print_lp(lp);
    
    // solve the lp
    int result_code = solve(lp);
    if (result_code == 0)
    {
        // print optimal value
        cout << "Largest Convexity we can get is: " << -1*get_objective(lp) << endl;
        
        // print the optimizing values of the variables
        get_variables(lp, solution);
        
        cout << "Optimal portfolio:" << endl;
        for (int i = 0; i < number_of_cash_flows; i++) {
            cout << "%Cash Flow:" << i+1 << "  ";
            //cout << solution[i]*percentage_of_cash_flow_to_meet_debt_obligation[i] << endl;
            cout << solution[i] << endl;
        }
        cout << endl << "That is, buy" << endl;
        for (int i = 0; i < number_of_cash_flows; i++)
            if (solution[i] !=0) {
                cout << "$" << price_list[i]*solution[i];
                cout << " of Cash Flow#" << i+1 << endl;
            }
    }
    else
    {
        cout << "There is no portfolio that meets the duration constraint of ";
        cout << time_when_debt_is_due << " years" << endl;
    }
    
}

int main (int argc, char* argv[])
{
    if (argc == 1) {
        cout << "Input filename missing" << endl;
    }
    else
    {
        get_data(argv);
        
        print_data(argv[1]);
        
        get_optimal_portfolio();
    }
    return (0);
}

