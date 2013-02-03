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
	cout << "Exponential distribution..." << endl;
	double lambda = 0.7;
	dg = new TFMDistributionGenerator(new ExponentialDistribution(lambda), 123456);
	genAndSave(dg, "exp.fout", N);
	
	// Normal
	cout << "Normal distribution..." << endl;
	double mean = 1.5; double sigma = 2.0;
	dg = new NormalDistributionGenerator(mean, sigma, 123456);
	genAndSave(dg, "normal.fout", N);
	
	// Normal with GAR
	cout << "Normal distribution (with GAR)..." << endl;
	mean = -3.2; sigma = 1.5;
	dg = new NormalGARGenerator(mean, sigma);
	genAndSave(dg, "normalGAR.fout", N);
	
	cout << "All done!" << endl;
	
	return 0;
}
