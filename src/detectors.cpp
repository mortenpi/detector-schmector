#include "detectors.hpp"

Detector::Detector(detectorparams param) {
	this->params = param;
}

IdealDetector::IdealDetector(detectorparams param) : Detector(param) {}

detectordata IdealDetector::simulate(particle p) {
	detectordata ret;
	ret.energy = p.energy;
	
	return ret;
}
