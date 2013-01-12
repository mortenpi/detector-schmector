#include <cmath>

#include "detectors.hpp"

Detector::Detector(detectorparams param) {
	this->params = param;
}

IdealDetector::IdealDetector(detectorparams param) : Detector(param) {}

double getYEst(double y, double dy) {
	return dy*floor((y+dy/2)/dy);
}

detectordata IdealDetector::simulate(particle p) {
	detectordata ret;
	ret.energy = p.energy; // no energy is lost
	
	double v = sqrt(2*p.energy / p.mass);
	double r = (p.mass * v)/(p.charge * this->params.B);
	
	double x0 = r * cos(p.phi - M_PI_2);
	double y0 = r * sin(p.phi - M_PI_2);
	
	// check max Dx
	double mDx = (this->params.dx*(this->params.N-1) + this->params.x0 - x0);
	if(fabs(mDx) > r) {
		// Badstuff.
		ret.energy = -1;
		return ret;
	}
	
	for(int i=0; i < this->params.N; i++) {
		double x = this->params.dx*i + this->params.x0;
		double Dx = x - x0;
		double Dy = sqrt(r*r - Dx*Dx);
		
		ret.points.push_back(point(x, getYEst(Dy, this->params.dy)));
	}
	
	return ret;
}
