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
	printf("\n\n");
	
	printf("### GAR normal distribution ###\n");
	NormalGARGenerator garng(0.0, 1.0);
	
	printf("> g(x):\n");
	for(int i=0, N=40; i<N; i++) {
		double x = 10*double(i)/(N-1) - 5.0;
		double y = garng.g(x);
		printf("(%7.3f, %7.3f) ", x, y);
		if(i%4 == 3) printf("\n");
	}
	printf("\n");
	
	printf("> g_invcdf(x):\n");
	for(int i=0, N=80; i<N; i++) {
		double x = double(i)/(N-1);
		double y = garng.g_invcdf(x);
		printf("(%7.3f, %7.3f) ", x, y);
		if(i%4 == 3) printf("\n");
	}
	printf("\n");
	
	double sum = 0.0;
	for(int i=0; i<1500; i++) {
		double x = garng.rnd();
		sum += x;
		printf("%6.2f ", x);
		if(i%15 == 14) printf("\n");
	}
	printf("Mean: %f\n", sum/400);
	printf("\n");
	
	return 0;
}
