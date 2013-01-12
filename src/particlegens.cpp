#include "particlegens.hpp"

ConstantParticleGenerator::ConstantParticleGenerator(double mass, double charge, double energy, double angle) {
	this->p.mass = mass;
	this->p.charge = charge;
	this->p.energy = energy;
	this->p.angle = angle;
}

particle ConstantParticleGenerator::generate() {
	return this->p;
}
