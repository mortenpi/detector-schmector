#include "structures.hpp"

class ParticleGenerator {
	public:
	virtual particle generate() = 0;
};

class ConstantParticleGenerator : public ParticleGenerator {
	particle p;
	
	public:
	ConstantParticleGenerator(double mass, double charge, double energy, double phi);
	particle generate();
};
