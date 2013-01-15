#include <cmath>

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
	this->width = max-min;
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

NormalDistributionGenerator::NormalDistributionGenerator(double mean, double sigma, int seed) : DistributionGenerator(seed) {
	this->dist = new NormalDistribution(mean, sigma);
	this->ymax = 1/(sigma*sqrt(2*M_PI));
	this->xmin = mean - 5*sigma;
	this->xmax = mean + 5*sigma;
}

double NormalDistributionGenerator::rnd() {
	double x,y;
	do{
		x = (this->xmax-this->xmin)*this->uniform() + this->xmin;
		y = this->ymax*this->uniform();
	} while(y > this->dist->pdf(x));
	return x;
}
