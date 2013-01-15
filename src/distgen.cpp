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

UniformDistributionGenerator::UniformDistributionGenerator(double a, double b, int seed) : DistributionGenerator(seed) {
	double min = (a<b)?a:b; double max = (a>b)?a:b;
	this->width = min-min;
	this->shift = min;
}

double UniformDistributionGenerator::rnd() {
	return this->width*this->uniform()+this->shift;
}

DeltaDistributionGenerator::DeltaDistributionGenerator(double x) : DistributionGenerator(0) {
	this->mean = x;
}

double DeltaDistributionGenerator::rnd() {
	return this->mean;
}
