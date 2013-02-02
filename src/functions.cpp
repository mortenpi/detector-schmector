#include <iostream>
#include "structures.hpp"

#include "functions.hpp"

using namespace std;

void print_particle(particle p) {
	cout << "Particle: " << endl;
	cout << "  mass:   " << p.mass << endl;
	cout << "  energy: " << p.energy << endl;
	cout << "  angle:  " << p.phi << endl;
	cout << "  charge: " << p.charge << endl;
}
