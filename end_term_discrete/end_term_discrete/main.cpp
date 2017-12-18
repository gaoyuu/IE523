// Down-and-out European Discrete Barrier Option Pricing Code written by Prof. Sreenivas
// discuss with Jiahao Huang
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <random>
#include <algorithm>
#include "newmat.h"
#include "normdist.h"
#include <math.h>
#include <chrono>

#define pi 3.141592653589793
using namespace std;

unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

double up_factor, uptick_prob;
double risk_free_rate, strike_price,initial_stock_price, barrier_price;
double expiration_time, volatility, R;
double call_cts, put_cts;
int no_of_divisions, no_of_samples;

double max(double a, double b) {
    return (b < a) ? a : b;
}

double get_uniform()
{
    std::uniform_real_distribution<double>distribution(0.0, 1.0);
    double number = distribution(generator);
    return (number);
}

double N(const double& z) {
    if (z > 6.0) { return 1.0; }; // this guards against overflow
    if (z < -6.0) { return 0.0; };
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274429;
    double p = 0.2316419;
    double c2 = 0.3989423;
    double a = fabs(z);
    double t = 1.0 / (1.0 + a*p);
    double b = c2*exp((-z)*(z / 2.0));
    double n = ((((b5*t + b4)*t + b3)*t + b2)*t + b1)*t;
    n = 1.0 - b*n;
    if (z < 0.0) n = 1.0 - n;
    return n;
}

double european_discrete_down_and_out_call_option() {
    double R = (risk_free_rate - 0.5*volatility*volatility)*expiration_time;
    double SD = volatility*sqrt(expiration_time);
    double result[4];
    double S1 = initial_stock_price;
    double S2 = initial_stock_price;
    double S3 = initial_stock_price;
    double S4 = initial_stock_price;
    double x = get_uniform();
    double y = get_uniform();
    double a = sqrt(-2.0*log(x)) * cos(2*pi*y);
    double b = sqrt(-2.0*log(x)) * sin(2*pi*y);
    result[0] = S1*exp(R + SD*a);
    result[1] = S2*exp(R - SD*a);
    result[2] = S3*exp(R + SD*b);
    result[3] = S4*exp(R - SD*b);
    double discrete_call_price = 0.0;
    
    for (int i = 0; i < 4; i++) {
        double ST = result[i];
        double PD = 1.0;
        
        Matrix mean_at_sampling_instant(no_of_divisions, 1);
        Matrix variance_at_sampling_instant(no_of_divisions, 1);
        
        if (ST > barrier_price) {
            for (int j = 1; j <= no_of_divisions; j++) {
                mean_at_sampling_instant(j, 1) = initial_stock_price +
                (((double)j) / ((double)no_of_divisions)*(ST - initial_stock_price));
                variance_at_sampling_instant(j, 1) = (((float)j) / ((float)no_of_divisions))*expiration_time*
                (1.0 - ((float)j) / ((float)no_of_divisions));
            }
            for (int j = 1; j <= no_of_divisions; j++) {
                PD *= (1.0 - N((barrier_price - mean_at_sampling_instant(j, 1)) / sqrt(variance_at_sampling_instant(j, 1))));
            }
            discrete_call_price = discrete_call_price + max(0.0, ST - strike_price)*PD;
        }
        else {
            discrete_call_price = discrete_call_price;
        }
    }
    return discrete_call_price/4.0;
}

double european_discrete_down_and_out_put_option() {
    double delta_T = expiration_time / ((double)no_of_divisions);
    double R = (risk_free_rate - 0.5*pow(volatility, 2))*delta_T;
    double SD = volatility*sqrt(delta_T);
    double result[4], valid[4];
    double S1 = initial_stock_price;
    double S2 = initial_stock_price;
    double S3 = initial_stock_price;
    double S4 = initial_stock_price;
    int valid1 = 1; int valid2 = 1; int valid3 = 1; int valid4 = 1;
    
    for (int k = 1; k <= no_of_divisions; k++) {
        double x = get_uniform();
        double y = get_uniform();
        double a = sqrt(-2.0*log(x)) * cos(2*pi*y);
        double b = sqrt(-2.0*log(x)) * sin(2*pi*y);
        S1 = S1*exp(R + SD*a);
        S2 = S2*exp(R - SD*a);
        S3 = S3*exp(R + SD*b);
        S4 = S4*exp(R - SD*b);
        if (S1 <= barrier_price) {
            valid1 = 0;
        }
        if (S2 <= barrier_price) {
            valid2 = 0;
        }
        if (S3 <= barrier_price) {
            valid3 = 0;
        }
        if (S4 <= barrier_price) {
            valid4 = 0;
        }
    }
    valid[0] = valid1; valid[1] = valid2; valid[2] = valid3; valid[3] = valid4;
    result[0] = S1; result[1] = S2; result[2] = S3; result[3] = S4;
    double discrete_put_price = 0.0;
    
    for (int i = 0; i < 4; i++) {
        double ST = result[i];
        int valid0 = valid[i];
        double PD = 1;
        
        Matrix mean_at_sampling_instant(no_of_divisions, 1);
        Matrix variance_at_sampling_instant(no_of_divisions, 1);
        
        for (int j = 1; j <= no_of_divisions; j++) {
            mean_at_sampling_instant(j, 1) = initial_stock_price +
            (((double)j) / ((double)no_of_divisions)*(ST - initial_stock_price));
            variance_at_sampling_instant(j, 1) = (((double)j) / ((double)no_of_divisions))*expiration_time*
            (1.0 - ((double)j) / ((double)no_of_divisions));
        }
        for (int j = 1; j <= no_of_divisions; j++) {
            PD *= (1.0 - N((barrier_price - mean_at_sampling_instant(j, 1)) / sqrt(variance_at_sampling_instant(j, 1))));
        }
        discrete_put_price = discrete_put_price + max(0.0, strike_price - ST)*PD*valid0;
    }
    return discrete_put_price/4.0;
}

void european_continue_down_and_out_option() {
    int k;
    double delta_T = expiration_time / ((double)no_of_divisions);
    double delta_R = (risk_free_rate - 0.5*pow(volatility, 2))*delta_T;
    double delta_SD = volatility*sqrt(delta_T);
    
    double S1 = initial_stock_price;
    double S2 = initial_stock_price;
    double S3 = initial_stock_price;
    double S4 = initial_stock_price;
    int valid1 = 1;  int valid2 = 1; int valid3 = 1; int valid4 = 1;
    
    for (k = 1; k <= no_of_divisions; k++) {
        double x = get_uniform();
        double y = get_uniform();
        double a = sqrt(-2.0*log(x)) * cos(2*pi*y);
        double b = sqrt(-2.0*log(x)) * sin(2*pi*y);
        S1 = S1*exp(delta_R + delta_SD*a);
        S2 = S2*exp(delta_R - delta_SD*a);
        S3 = S3*exp(delta_R + delta_SD*b);
        S4 = S4*exp(delta_R - delta_SD*b);
        if (S1 <= barrier_price) {
            valid1 = 0;
        }
        if (S2 <= barrier_price) {
            valid2 = 0;
        }
        if (S3 <= barrier_price) {
            valid3 = 0;
        }
        if (S4 <= barrier_price) {
            valid4 = 0;
        }
    }
    call_cts = (max(0.0, S1 - strike_price)*valid1 + max(0.0, S2 - strike_price)*valid2
            + max(0.0, S3 - strike_price)*valid3 + max(0.0, S4 - strike_price)*valid4) / 4;
    put_cts = (max(0.0, strike_price - S1)*valid1 + max(0.0, strike_price - S2)*valid2
               + max(0.0, strike_price - S3)*valid3 + max(0.0, strike_price - S4)*valid4) / 4.0;
}


int main(int argc, char* argv[])
{
    sscanf (argv[1], "%lf", &expiration_time);
    sscanf (argv[2], "%lf", &risk_free_rate);
    sscanf (argv[3], "%lf", &volatility);
    sscanf (argv[4], "%lf", &initial_stock_price);
    sscanf (argv[5], "%lf", &strike_price);
    sscanf (argv[6], "%d", &no_of_samples);
    sscanf (argv[7], "%d", &no_of_divisions);
    sscanf (argv[8], "%lf", &barrier_price);
    
    up_factor = exp(volatility*sqrt(expiration_time / ((double)no_of_divisions)));
    R = exp(risk_free_rate*expiration_time / ((double)no_of_divisions));
    uptick_prob = (R - (1 / up_factor)) / (up_factor - (1 / up_factor));
    
    double call_option_price = 0.0;
    double put_option_price = 0.0;
    double barrier_call_option = 0.0;
    double barrier_put_option = 0.0;
    
    for (int i = 0; i < no_of_samples; i++) {
        
        european_continue_down_and_out_option();
        
        double call_dis = european_discrete_down_and_out_call_option();
        double put_dis = european_discrete_down_and_out_put_option();
        
        call_option_price = call_option_price + call_cts;
        put_option_price = put_option_price + put_cts;
        barrier_call_option = barrier_call_option + call_dis;
        barrier_put_option = barrier_put_option + put_dis;
    }
    
    call_option_price = exp(-risk_free_rate * expiration_time) * (call_option_price / ((double)no_of_samples));
    put_option_price  = exp(-risk_free_rate * expiration_time) * (put_option_price / ((double)no_of_samples));
    barrier_call_option  = exp(-risk_free_rate * expiration_time) * (barrier_call_option / ((double)no_of_samples));
    barrier_put_option   = exp(-risk_free_rate * expiration_time) * (barrier_put_option / ((double)no_of_samples));


    
    cout << "European Down and Out Discrete Barrier Option Pricing" << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility * 100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "Barrier Price = " << barrier_price << endl;
    cout << "Number of (uniformly spaced) Discrete Barrier-Samples = " << no_of_samples << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "--------------------------------------" << endl;
    cout << "The Average Call Price via Explicit Simulation of Price Paths =    " << call_option_price << endl;
    cout << "Price of an European Down and Out Discrete Barrier Call Option =   " << barrier_call_option << endl;
    cout << "The Average Put Price via Explicit Simulation of Price Paths =     " << put_option_price << endl;
    cout << "Price of an European Down and Out Discrete Barrier Put Option =    " << barrier_put_option << endl;
    cout << "--------------------------------------" << endl;
    
    return 0;
}


