// American-Asian Option Pricing using recursion
// Written by Prof. R.S. Sreenivas for IE523: Financial Computing
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

float up_factor, uptick_prob, risk_free_rate, strike_price;
float initial_stock_price, expiration_time, volatility, R;
int no_of_divisions;

float max(float a, float b) {
    return (b < a )? a:b;
}

float american_asian_call_option(int k, int i, float current_stock_price, float current_average_stock_price) {
    if (k == no_of_divisions)
        return max(0.0, (current_average_stock_price - strike_price));
    else
        return max((current_average_stock_price - strike_price), (uptick_prob*american_asian_call_option(k+1, i+1, current_stock_price*up_factor, ((k*current_average_stock_price) + (current_stock_price*up_factor))/((float) k+1)) + (1-uptick_prob)*american_asian_call_option(k+1, i-1, current_stock_price/up_factor, ((k*current_average_stock_price) + (current_stock_price/up_factor))/((float) k+1)))/R);
}

float american_asian_put_option(int k, int i, float current_stock_price, float current_average_stock_price) {
    if (k == no_of_divisions)
        return max(0.0, (strike_price - current_average_stock_price));
    else
        return max((strike_price - current_average_stock_price),
                   (uptick_prob*american_asian_put_option(k+1, i+1, current_stock_price*up_factor, ((k*current_average_stock_price) + (current_stock_price*up_factor))/((float) k+1)) + (1-uptick_prob)*american_asian_put_option(k+1, i-1, current_stock_price/up_factor, ((k*current_average_stock_price) + (current_stock_price/up_factor))/((float) k+1)))/R);
}

int main (int argc, char* argv[])
{
    
    sscanf (argv[1], "%f", &expiration_time);
    sscanf (argv[2], "%d", &no_of_divisions);
    sscanf (argv[3], "%f", &risk_free_rate);
    sscanf (argv[4], "%f", &volatility);
    sscanf (argv[5], "%f", &initial_stock_price);
    sscanf (argv[6], "%f", &strike_price);
    
    up_factor = exp(volatility*sqrt(expiration_time/((float) no_of_divisions)));
    R = exp(risk_free_rate*expiration_time/((float) no_of_divisions));
    uptick_prob = (R - (1/up_factor))/(up_factor-(1/up_factor));
    cout << "Recursive Binomial American-Asian Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility*100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "--------------------------------------" << endl;
    cout << "Binomial Price of an American-Asian Call Option = " << american_asian_call_option(0, 0,initial_stock_price, initial_stock_price) << endl;
    cout << "Binomial Price of an American-Asian Put Option = " << american_asian_put_option(0, 0, initial_stock_price, initial_stock_price) << endl;
}
