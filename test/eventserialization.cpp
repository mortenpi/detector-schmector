#include <iostream>
#include <fstream>

#include "event.hpp"

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

struct vec {
	double x,y,z;
};

template<class Archive>
void serialize(Archive & ar, vec &v, const unsigned int version) {
	ar & v.x;
	ar & v.y;
	ar & v.z;
}

void printEvent(const Event &e) {
	cout << "Has particle? " << (e.has_p?"Yes!":"No!") << endl;
	if(e.has_p) {
		cout << " > mass   = " << e.p.mass << endl;
		cout << " > charge = " << e.p.charge << endl;
		cout << " > energy = " << e.p.energy << endl;
		cout << " > phi    = " << e.p.phi << endl;
	}
	
	cout << "Has detector params? " << (e.has_dp?"Yes!":"No!") << endl;
	if(e.has_dp) {
		//cout << " > " << e.p.phi << endl;
	}
	
	cout << "Has detector data? " << (e.has_d?"Yes!":"No!") << endl;
	if(e.has_d) {
		cout << " > energy = " << e.d.energy << endl;
		cout << " > N = " << e.d.points.size() << endl;
		for(int i=0; i<e.d.points.size(); i++) {
			point ppp = e.d.points[i];
			cout << " > p(" << ppp.x << ", " << ppp.y << ")" << endl;
		}
	}
	
	cout << "Has reco? " << (e.has_g?"Yes!":"No!") << endl;
	if(e.has_g) {
		cout << " > " << e.p.phi << endl;
	}
}

int main(int argc, char* argv[]) {
	Event ev;
	ev.has_p = true;
	ev.p.mass = 1200.8877;
	
	ev.has_d = true;
	ev.d.energy = 123;
	for(int i=0; i<3; i++) {
		ev.d.points.push_back(point(-5,5-i));
	}
	
	
	cout << endl;
	cout << "Particle as written:" << endl;
	printEvent(ev);
	cout << endl;
	
	cout << "Writing event" << endl;
	ofstream fout("bser.fout");
	boost::archive::text_oarchive oa(fout);
	oa << ev;
	fout.close();
	
	cout << "Written. Reading..." << endl;
	
	ifstream fin("bser.fout");
	boost::archive::text_iarchive ia(fin);
	ia >> ev;
	fin.close();
	
	cout << endl;
	cout << "Particle as read:" << endl;
	printEvent(ev);
	cout << endl;
	
	return 0;
}
