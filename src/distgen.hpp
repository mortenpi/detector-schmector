#ifndef _DISTGEN_HPP_
#define _DISTGEN_HPP_
#include <gsl/gsl_rng.h>
//#include "distributions.hpp"
class Distribution;

class DistributionGenerator {
	gsl_rng * rng;
	
	protected:
	double uniform();
	
	public:
	DistributionGenerator(int seed);
	virtual double rnd() = 0;
};

class TFMDistributionGenerator : public DistributionGenerator {
	Distribution * dist;
	
	public:
	TFMDistributionGenerator(Distribution * dist, int seed);
	virtual double rnd();
};

class NormalDistributionGenerator : public DistributionGenerator {
	Distribution * dist;
	double ymax; double xmin, xmax;
	
	public:
	NormalDistributionGenerator(double mean, double sigma, int seed);
	virtual double rnd();
};

class UniformDistributionGenerator : public DistributionGenerator {
	double width, shift;
	
	public:
	UniformDistributionGenerator(double a, double b, int seed);
	virtual double rnd();
};

class DeltaDistributionGenerator : public DistributionGenerator {
	double mean;
	
	public:
	DeltaDistributionGenerator(double x);
	virtual double rnd();
};
#endif
