#include <iostream>

#include "particlegens.hpp"
#include "detectors.hpp"
#include "reco.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 1; dp.dy = 0.1;
	dp.x0 = 0.3; dp.dx = 0.05; dp.N = 20;
	
	ParticleGenerator * pg = new ConstantParticleGenerator(1,2,3,4);
	Detector * d = new IdealDetector(dp);
	Reconstructor * r = new LSFCircleReco(dp);
	
	particle p = pg->generate();
	detectordata data = d->simulate(p);
	particleguess guess = r->reco(data);
	
	cout << "Particle: " << p.mass << ' ' << p.energy << endl;
	
	return 0;
}
