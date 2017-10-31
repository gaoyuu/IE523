#include <stdio.h>
#include <math.h>
#include <chplot.h>

/* The initial position of the vibration is 4.
 The initial velocity of the vibration is 0 */
double overdamped(double t) {
    return 4.12*exp(-1.57*t) - 0.12*exp(-54.2*t);
}

double criticaldamped(double t) {
    return 4*(1+6*t)*exp(-6*t);
}

double underdamped(double t) {
    return 4.06*exp(-0.5*t)*sin(3*t+1.4);
}

int main() {
    double t0, tf;
    int num = 100;       // number of points for plotting
    CPlot plot;
    
    t0 = 0;
    tf = 10;
    plot.title("Damped Free Vibration");
    plot.label(PLOT_AXIS_X, "time (second)");
    plot.label(PLOT_AXIS_Y, "x");
    plot.func2D(t0, tf, num, overdamped);
    plot.legend("overdamped", 0);
    plot.func2D(t0, tf, num, criticaldamped);
    plot.legend("critically damped", 1);
    plot.func2D(t0, tf, num, underdamped);
    plot.legend("underdamped", 2);
    plot.plotting();
    re
