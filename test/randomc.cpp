/**
 * RandomMC library test.
 */

#include <iostream>
#include "randomc/randomc.h"

using namespace std;

int main(int argc, char* argv[]) {
	CRandomMersenne rnd(4); // Determined by a fair dice roll
	cout << "Fair dice roll: " << rnd.Random() << endl;
	cout << "Fair dice roll: " << rnd.Random() << endl;
	cout << "Fair dice roll: " << rnd.Random() << endl;
	cout << "Fair dice roll: " << rnd.Random() << endl;
	cout << "Fair dice roll: " << rnd.Random() << endl;
	
	return 0;
}
