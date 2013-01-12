#include <iostream>

#include "particlegens.hpp"
#include "detectors.hpp"
#include "reco.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 1; dp.dy = 0.1;
	dp.x0 = 0.3; dp.dx = 0.05; dp.N = 20;
	
	ParticleGenerator * pg = new ConstantParticleGenerator(2,2,5,0);
	Detector * d = new IdealDetector(dp);
	Reconstructor * r = new LSFCircleReco(dp);
	
	particle p = pg->generate();
	detectordata data = d->simulate(p);
	particleguess guess = r->reco(data);
	
	cout << "Particle: " << p.mass << ' ' << p.energy << endl;
	cout << "Detector data:" << endl;
	cout << "  E = " << data.energy << endl;
	cout << "  Pts: " << data.points.size() << endl;
	for(int i=0; i<data.points.size(); i++) {
		point pt = data.points[i];
		cout << pt.x << ' ' << pt.y << endl;
	}
	
	return 0;
}
