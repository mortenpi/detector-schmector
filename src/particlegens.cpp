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
