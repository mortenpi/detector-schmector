/**
 * @file
 * Abstract and implemented classes of probability distributions.
 */
#ifndef _DISTRIBUTIONS_HPP_
#define _DISTRIBUTIONS_HPP_

/**
 * @brief Abstract base class of a probability distribution.
 * Requires the probability distribution to have the following
 * methods:
 *  -  probability density function (PDF)
 *  -  cumulative probablility function (CDF)
 *  -  inverse of the CDF
 */
class Distribution {
	public:
	virtual double pdf(double x) = 0;
	virtual double cdf(double x) = 0;
	virtual double invcdf(double p) = 0;
};

/**
 * @brief Implements the normal distribution
 * A normal (aka Gaussian) distribtuion of a specified
 * mean and standard deviation.
 */
class NormalDistribution: public Distribution {
	double A, B, mean;
	
	public:
	NormalDistribution(double mean, double stdev);
	double pdf(double x);
	double cdf(double x);
	double invcdf(double p);
};

/**
 * @brief Implements the decaying exponential distribution
 * lambda is the decay coefficient. Note: PDF(x < 0) = 0
 */
class ExponentialDistribution: public Distribution {
	double lambda;
	
	public:
	ExponentialDistribution(double lambda);
	double pdf(double x);
	double cdf(double x);
	double invcdf(double p);
};

#endif
