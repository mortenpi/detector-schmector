#include "particlegens.hpp"

ConstantParticleGenerator::ConstantParticleGenerator(double mass, double charge, double energy, double phi) {
	this->p.mass = mass;
	this->p.charge = charge;
	this->p.energy = energy;
	this->p.phi = phi;
}

particle ConstantParticleGenerator::generate() {
	return this->p;
}

DistributedParticleGenerator::DistributedParticleGenerator(DistributionGenerator * massDistGen, DistributionGenerator * chargeDistGen, DistributionGenerator * energyDistGen, DistributionGenerator * phiDistGen) {
	this->massDistGen = massDistGen;
	this->chargeDistGen = chargeDistGen;
	this->energyDistGen = energyDistGen;
	this->phiDistGen = phiDistGen;
}

particle DistributedParticleGenerator::generate() {
	particle p;
	p.mass   = this->massDistGen->rnd();
	p.charge = this->chargeDistGen->rnd();
	p.energy = this->energyDistGen->rnd();
	p.phi    = this->phiDistGen->rnd();
	return p;
}
