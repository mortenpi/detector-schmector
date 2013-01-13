#include <iostream>
#include <fstream>
#include <cmath>

#include "structures.hpp"
#include "simulator.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 4; dp.dy = 0.03;
	dp.x0 = 0.2; dp.dx = 0.05; dp.N = 20;
	
	Simulator s(
		new ConstantParticleGenerator(5,2,5,3.1415/4),
		new IdealDetector(dp),
		new SimpleLSFCircleReco(dp),
		dp
	);
	
	s.run("test.fout", 1000);
	
	return 0;
}
