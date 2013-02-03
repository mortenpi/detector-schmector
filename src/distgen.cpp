#include <cmath>
#include <gsl/gsl_rng.h>
#include "distributions.hpp"

#include "distgen.hpp"

/** DistributionGenerator **/
DistributionGenerator::DistributionGenerator(int seed) {
	this->rng = gsl_rng_alloc(gsl_rng_mt19937);
}

double DistributionGenerator::uniform() {
	return gsl_rng_uniform_pos(this->rng);
}

/** TFMDistributionGenerator **/
TFMDistributionGenerator::TFMDistributionGenerator(Distribution * dist, int seed) : DistributionGenerator(seed) {
	this->dist = dist;
}

double TFMDistributionGenerator::rnd() {
	return this->dist->invcdf(this->uniform());
}

/** UniformDistributionGenerator **/
UniformDistributionGenerator::UniformDistributionGenerator(double a, double b, int seed) : DistributionGenerator(seed) {
	double min = (a<b)?a:b; double max = (a>b)?a:b;
	this->width = max-min;
	this->shift = min;
}

double UniformDistributionGenerator::rnd() {
	return this->width*this->uniform()+this->shift;
}

double UniformDistributionGenerator::rnd_c(double a, double b) {
	return (b-a)*this->uniform()+a;
}

/** DeltaDistributionGenerator **/
DeltaDistributionGenerator::DeltaDistributionGenerator(double x) : DistributionGenerator(0) {
	this->mean = x;
}

double DeltaDistributionGenerator::rnd() {
	return this->mean;
}

/** NormalDistributionGenerator **/
NormalDistributionGenerator::NormalDistributionGenerator(double mean, double sigma, double k, int seed) : DistributionGenerator(seed) {
	this->dist = new NormalDistribution(mean, sigma);
	this->ymax = 1/(sigma*sqrt(2*M_PI));
	this->xmin = mean - k*sigma;
	this->xmax = mean + k*sigma;
}

double NormalDistributionGenerator::rnd() {
	double x,y;
	do{
		x = (this->xmax-this->xmin)*this->uniform() + this->xmin;
		y = this->ymax*this->uniform();
	} while(y > this->dist->pdf(x));
	return x;
}

/** NormalGARGenerator **/
NormalGARGenerator::NormalGARGenerator(double mean, double sigma, double k, int seed) : DistributionGenerator(seed) {
	this->dist = new NormalDistribution(0, sigma);
	
	this->mean = mean;
	this->sigma = sigma;
	this->x0 = k*sigma;
	this->ymax = 1/(sigma*sqrt(2*M_PI));
	this->lambda = k/(2*sigma);
	this->k = k;
	
	this->pdf_norm = sqrt(2.0/M_PI)*( (2/k)*exp(-0.5*k*k) + k );
	this->cdf_x0 = (1/this->pdf_norm)*(1/k)*sqrt(2.0/M_PI)*exp(-0.5*k*k);
}

double NormalGARGenerator::rnd() {
	double x,y;
	do{
		x = this->g_invcdf( this->uniform() );
		y = this->g(x)*this->uniform();
	} while(y > this->dist->pdf(x));
	return x + this->mean;
}

double NormalGARGenerator::g(double x) {
	if(fabs(x) > this->x0) {
		return this->ymax*exp( (-1)*this->lambda*fabs(x) );
	} else {
		return this->ymax;
	}
}

double NormalGARGenerator::g_invcdf(double px) {
	if(px < this->cdf_x0) {
		return log( sqrt(M_PI/2)*k*this->pdf_norm*px )/this->lambda;
	} else if(px > (1-this->cdf_x0)) {
		return (-1)*log( sqrt(M_PI/2)*k*this->pdf_norm*(1-px) )/this->lambda;
	} else {
		return this->sigma*sqrt(2*M_PI)*( this->pdf_norm*(px-this->cdf_x0) - k/sqrt(2*M_PI) );
	}
}
