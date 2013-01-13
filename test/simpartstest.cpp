#include <iostream>
#include <fstream>
#include <cmath>

#include "particlegens.hpp"
#include "detectors.hpp"
#include "reco.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 4; dp.dy = 0.03;
	dp.x0 = 0.2; dp.dx = 0.05; dp.N = 20;
	
	ParticleGenerator * pg = new ConstantParticleGenerator(5,2,5,3.1415/4);
	Detector * d = new IdealDetector(dp);
	//Reconstructor * r = new LSFCircleReco(dp);
	Reconstructor * r = new SimpleLSFCircleReco(dp);
	
	particle p = pg->generate();
	detectordata data = d->simulate(p);
	particleguess guess = r->reco(data);
	
	cout << "Particle: " << endl;
	cout << "  mass:   " << p.mass << endl;
	cout << "  energy: " << p.energy << endl;
	cout << "  angle:  " << p.phi << endl;
	cout << "  charge: " << p.charge << endl;
	
	cout << endl;
	cout << "Detector data:" << endl;
	cout << "  E = " << data.energy << endl;
	cout << "  Pts: " << data.points.size() << endl;
	
	cout << "  > Writing to `pts.csv`" << endl;
	ofstream fout("pts.csv");
	fout << "x, y" << endl;
	fout << guess.cx << ", " << guess.cy << ", " << guess.cr << endl;
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
	cout << " angle guess = " << guess.phi << endl;
	cout << " angle guess = " << (180/M_PI)*guess.phi << " deg" << endl;
	
	return 0;
}
