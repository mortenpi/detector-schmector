#include <iostream>
#include <fstream>
#include <cmath>

#include "distributions.hpp"
#include "distgen.hpp"

using namespace std;

void genAndSave(DistributionGenerator * dg, const char* fname, int N) {
	ofstream fout(fname);
	for(int i = 0; i<N; i++) {
		fout << dg->rnd() << endl;
	}
	fout.close();
}

int main(int argc, char* argv[]) {
	DistributionGenerator * dg;
	int N = 10000;
	
	// Exponential
	double lambda = 0.7;
	dg = new TFMDistributionGenerator(new ExponentialDistribution(lambda), 123456);
	genAndSave(dg, "exp.fout", N);
	
	// Normal
	double mean = 1.5; double sigma = 2.0;
	dg = new NormalDistributionGenerator(mean, sigma, 123456);
	genAndSave(dg, "normal.fout", N);
	
	return 0;
}
