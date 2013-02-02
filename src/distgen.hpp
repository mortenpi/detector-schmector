/**
 * @file
 * Header file for the random number generators. These classes can
 * be used to create random numbers that adhere to a specific
 * probability distribution.
 */
#ifndef _DISTGEN_HPP_
#define _DISTGEN_HPP_

#include <gsl/gsl_rng.h>
class Distribution;

/**
 * @brief Abstract base class of a distribution generator.
 * It provides a GSL based random number generator that the deriving
 * classes can use.
 */
class DistributionGenerator {
	gsl_rng * rng; // pointer to the GSL generator
	
	protected:
	/**
	 * Returns a random double in the range (0,1).
	 * Note that the numbers 0 and 1 are excluded.
	 */
	double uniform();
	
	public:
	DistributionGenerator(int seed);
	/**
	 * Create a random double that adheres to a distribution.
	 */
	virtual double rnd() = 0;
};

/**
 * @brief Transformation method based distribution generator.
 * It uses the cumulative distribution function of the provided
 * distribution to generate random numbers adhering to the distribution.
 */
class TFMDistributionGenerator : public DistributionGenerator {
	Distribution * dist;
	
	public:
	TFMDistributionGenerator(Distribution * dist, int seed);
	virtual double rnd();
};

/**
 * @brief Normal distribution generator
 * Internally the acceptance-rejection method is used to create random
 * numbers that adhere to the normal distribution. Only numbers up to
 * five sigma from the mean are generated.
 */
class NormalDistributionGenerator : public DistributionGenerator {
	Distribution * dist;
	double ymax; double xmin, xmax;
	
	public:
	NormalDistributionGenerator(double mean, double sigma, int seed);
	virtual double rnd();
};

/**
 * @brief Uniformly distributed random numbers.
 */
class UniformDistributionGenerator : public DistributionGenerator {
	double width, shift;
	
	public:
	UniformDistributionGenerator(double a, double b, int seed);
	virtual double rnd();
};

/**
 * @brief Delta distribution.
 * I.e. it simply returns the parameter.
 */
class DeltaDistributionGenerator : public DistributionGenerator {
	double mean;
	
	public:
	DeltaDistributionGenerator(double x);
	virtual double rnd();
};

#endif
