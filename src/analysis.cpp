#include <iostream>
#include <fstream>
#include <cmath>

#include "structures.hpp"
#include "functions.hpp"
#include "distributions.hpp"
#include "distgen.hpp"
#include "simulator.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	detectorparams dp;
	dp.B = 4; dp.dy = 0.03;
	dp.x0 = 0.2; dp.dx = 0.05; dp.N = 20;
	
	DistributedParticleGenerator * dpg =
		new DistributedParticleGenerator(
			new DeltaDistributionGenerator(5),
			new DeltaDistributionGenerator(2),
			new NormalDistributionGenerator(7, 0.5, 123456),
			new TFMDistributionGenerator(new ExponentialDistribution(5), 123456)
		);
	
	Simulator s(
		dpg,
		new IdealDetector(dp),
		new SimpleLSFCircleReco(dp),
		dp
	);
	
	s.run("distevts.fout", 100000);
	
	return 0;
}
