#include "particlegens.hpp"
#include "detectors.hpp"
#include "reco.hpp"

class Simulator {
	ParticleGenerator * pg;
	Detector * det;
	Reconstructor * reco;
	detectorparams dp;
	
	public:
	Simulator(ParticleGenerator * pg, Detector * det, Reconstructor * reco, detectorparams dp);
	void run(const char * file, int N);
};
