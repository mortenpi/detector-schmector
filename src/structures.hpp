#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_

#include <vector>

struct particle {
	double mass, charge, energy, angle;
};

struct particleguess {
	double mass, charge, energy, angle;
};

struct detectorparams {
	double x0, dx, N;
	double dy;
	double B;
};

struct point {
	double x,y;
};

struct detectordata {
	double energy;
	std::vector<point> points;
};

#endif
