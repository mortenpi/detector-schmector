//#include "distributions.hpp"
class Distribution;
class CRandomMersenne;

class DistributionGenerator {
	CRandomMersenne * gen;
	
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
