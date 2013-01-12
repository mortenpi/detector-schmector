#include <vector>

struct particle {
	double mass, charge, energy, angle;
};

struct detectorparams {
	double x0, dx, N;
	double dy;
};

struct point {
	double x,y;
};

struct detectordata {
	double energy;
	std::vector<point> points;
};

