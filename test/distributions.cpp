/**
 * Test of the distributions classes.
 */

#include <cstdio>
#include "distributions.hpp"

int main(int argc, char* argv[]) {
	Distribution * pdists[] = {
		new ExponentialDistribution(0.2),
		new NormalDistribution(1.5, 1)
	};
	int len_pdists = sizeof(pdists)/sizeof(Distribution*);
	
	printf("%i\n", len_pdists);
	
	for(int i=0; i < len_pdists; i++) {
		Distribution * pdist = pdists[i];
		for(int n=0; n < 11; n++) {
			double x = 0.5*(n-5);
			double pdf = pdist->pdf(x);
			double cdf = pdist->cdf(x);
			double icdf = pdist->invcdf(cdf);
			printf("%6.3f %6.3f %6.3f %6.3f\n", x, pdf, cdf, icdf);
		}
	}

	return 0;
}
