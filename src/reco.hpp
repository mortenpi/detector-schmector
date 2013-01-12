#include "structures.hpp"

class Reconstructor {
	detectorparams params;
	
	public:
	Reconstructor(detectorparams param);
	virtual particleguess reco(detectordata d) = 0;
};

class LSFCircleReco : public Reconstructor {
	public:
	LSFCircleReco(detectorparams param);
	particleguess reco(detectordata d);
};
