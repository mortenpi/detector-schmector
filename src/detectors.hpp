#include "structures.hpp"

class Detector {
	detectorparams params;
	
	public:
	Detector(detectorparams param);
	virtual detectordata simulate(particle p) = 0;
};

class IdealDetector : public Detector {
	public:
	IdealDetector(detectorparams param);
	detectordata simulate(particle p);
};
