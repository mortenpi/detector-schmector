#include <cmath>

#include "distributions.hpp"

ExponentialDistribution::ExponentialDistribution(double lambda) {
	this->lambda = lambda;
}

double ExponentialDistribution::pdf(double x) {
	if(x>=0) {
		return this->lambda * exp( (-1) * this->lambda * x );
	} else {
		return 0;
	}
}

double ExponentialDistribution::cdf(double x) {
	if(x>0) {
		return 1 - exp( (-1) * this->lambda * x );
	} else {
		return 0;
	}
}

double ExponentialDistribution::invcdf(double p) {
	if(p <= 0) {
		return 0;
	} else if(p >= 1) {
		return 1000;
	} else {
		return (-1/this->lambda)*log(1 - p);
	}
}

NormalDistribution::NormalDistribution(double mean, double stdev) {
	this->mean = mean;
	this->A = 1/(stdev*sqrt(2 * M_PI));
	this->B = (-1)/(2*stdev*stdev);
}

double NormalDistribution::pdf(double x) {
	double x0 = x - this->mean;
	return A*exp(B*x0*x0);
}

double NormalDistribution::cdf(double x) {return 0;} // TODO
double NormalDistribution::invcdf(double p) {return 0;} // TODO
