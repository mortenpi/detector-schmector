#include <iostream>

#include "particlegens.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	particle p;
	
	ParticleGenerator * pg = new ConstantParticleGenerator(1,2,3,4);
	p = pg->generate();
	cout << p.mass << ' ' << p.energy << endl;
	
	return 0;
}
