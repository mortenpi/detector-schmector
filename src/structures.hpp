#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_

#include <vector>

struct particle {
	double mass, charge, energy, phi;
};

struct particleguess {
	double mass, charge, energy, phi;
	double cr, cx, cy;
};

struct detectorparams {
	double x0, dx, N;
	double dy;
	double B;
};

struct point {
	double x,y;
	point(double x, double y) {
		this->x = x; this->y = y;
	}
	point() {}
};

struct detectordata {
	double energy;
	std::vector<point> points;
};

#endif
