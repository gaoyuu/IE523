// normdist.h

#ifndef _NORMAL_DIST_H_
#define _NORMAL_DIST_H_

double n(const double& z);                          // normal distribution function
double n(const double& r, const double& mu, const double& sigmasqr);
double N(const double& z);                          // cumulative probability of univariate normal
double N(const double& a, const double& b, const double& rho);// cumulative probability of bivariate normal
double random_normal(); // random numbers with mean zero and variance one
double random_uniform_0_1();
#endif
