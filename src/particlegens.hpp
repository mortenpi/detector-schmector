#include "structures.hpp"
#include "distgen.hpp"

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

class DistributedParticleGenerator : public ParticleGenerator {
	DistributionGenerator * massDistGen;
	DistributionGenerator * chargeDistGen;
	DistributionGenerator * energyDistGen;
	DistributionGenerator * phiDistGen;
	
	public:
	DistributedParticleGenerator(
		DistributionGenerator * massDistGen,
		DistributionGenerator * chargeDistGen,
		DistributionGenerator * energyDistGen,
		DistributionGenerator * phiDistGen
	);
	particle generate();
};
