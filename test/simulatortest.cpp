#include <iostream>
#include <fstream>

#include "particlegens.hpp"
#include "detectors.hpp"
#include "reco.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 4; dp.dy = 0.1;
	dp.x0 = 0.2; dp.dx = 0.001; dp.N = 100;
	
	ParticleGenerator * pg = new ConstantParticleGenerator(2,2,5,3.1415/4);
	Detector * d = new IdealDetector(dp);
	//Reconstructor * r = new LSFCircleReco(dp);
	Reconstructor * r = new SimpleLSFCircleReco(dp);
	
	particle p = pg->generate();
	detectordata data = d->simulate(p);
	particleguess guess = r->reco(data);
	
	cout << "Particle: " << p.mass << ' ' << p.energy << endl;
	
	cout << endl;
	cout << "Detector data:" << endl;
	cout << "  E = " << data.energy << endl;
	cout << "  Pts: " << data.points.size() << endl;
	
	cout << "  > Writing to `pts.csv`" << endl;
	ofstream fout("pts.csv");
	fout << "x, y" << endl;
	for(int i=0; i<data.points.size(); i++) {
		point pt = data.points[i];
		//cout << pt.x << ' ' << pt.y << endl;
		fout << pt.x << ", " << pt.y << endl;
	}
	fout.close();
	
	cout << endl;
	cout << "Reco data:" << endl;
	cout << "  x = " << guess.cx << endl;
	cout << "  y = " << guess.cy << endl;
	cout << "  t = " << guess.cr << endl;
	
	return 0;
}
