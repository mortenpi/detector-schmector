/**
 * Test of the distribution generators.
 */

#include <cstdio>
#include "distributions.hpp"
#include "distgen.hpp"

int main(int argc, char* argv[]) {
	ExponentialDistribution dist(0.2);
	DistributionGenerator * dg = new TFMDistributionGenerator(&dist, 0);
	
	for(int i=0; i<10; i++) {
		printf("%d: %f", i, dg->rnd());
	}
	
	return 0;
}
