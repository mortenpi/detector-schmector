#include "randomc/randomc.h"
#include "distributions.hpp"

#include "distgen.hpp"

DistributionGenerator::DistributionGenerator(int seed) {
	this->gen = new CRandomMersenne(seed);
}

double DistributionGenerator::uniform() {
	return this->gen->Random();
}

TFMDistributionGenerator::TFMDistributionGenerator(Distribution * dist, int seed) : DistributionGenerator(seed) {
	this->dist = dist;
}

double TFMDistributionGenerator::rnd() {
	return this->dist->invcdf(this->uniform());
}
