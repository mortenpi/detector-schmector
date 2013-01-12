#include "reco.hpp"

Reconstructor::Reconstructor(detectorparams param) {
	this->params = param;
}

LSFCircleReco::LSFCircleReco(detectorparams param) : Reconstructor(param) {}

particleguess LSFCircleReco::reco(detectordata d) {
	particleguess ret;
	return ret;
}
