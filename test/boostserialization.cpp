#include <iostream>
#include <fstream>

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

int main(int argc, char* argv[]) {
	vec vs[] = {
		{1.3, 1.4, 1.5},
		{2.3, 2.4, 2.5},
		{3.3, 3.4, 3.5}
	};
	int N = sizeof(vs)/sizeof(vs[0]);
	
	cout << N << " vectors." << endl;
	for(int i=0; i<N; i++) {
		vec v = vs[i];
		cout << v.x << ' ' << v.y << ' ' << v.z << endl;
	}
	
	ofstream fout("bser.fout");
	boost::archive::text_oarchive oa(fout);
	for(int i=0; i<N; i++) oa << vs[i];
	fout.close();
	
	cout << "Written. Reading..." << endl;
	
	ifstream fin("bser.fout");
	boost::archive::text_iarchive ia(fin);
	try {
		for(int i=0; i<N+1; i++) {
			vec v;
			ia >> v;
			cout << v.x << ' ' << v.y << ' ' << v.z << endl;
		}
	} catch(boost::archive::archive_exception e) {
		cout << "Exception: " << e.what() << endl;
	}
	fin.close();
	
	return 0;
}
