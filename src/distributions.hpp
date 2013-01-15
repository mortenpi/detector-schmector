#ifndef _DISTRIBUTIONS_HPP_
#define _DISTRIBUTIONS_HPP_
class Distribution {
	public:
	Distribution() {}
	virtual double pdf(double x) = 0;
	virtual double cdf(double x) = 0;
	virtual double invcdf(double p) = 0;
};

class NormalDistribution: public Distribution {
	double A, B, mean;
	
	public:
	NormalDistribution(double mean, double stdev);
	double pdf(double x);
	double cdf(double x);
	double invcdf(double p);
};

class ExponentialDistribution: public Distribution {
	double lambda;
	
	public:
	ExponentialDistribution(double lambda);
	double pdf(double x);
	double cdf(double x);
	double invcdf(double p);
};
#endif
