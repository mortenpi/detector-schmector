//#include <boost/serialization/access.hpp>
//#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "structures.hpp"

class Event {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & has_p; ar & has_dp; ar & has_d; ar & has_g;
		ar & p; ar & dp; ar & d; ar & g;
	}
	
	public:
	bool has_p, has_g, has_dp, has_d;
	
	particle p;
	detectorparams dp;
	detectordata d;
	particleguess g;
	
	Event() {
		this->has_p=false;
		this->has_g=false;
		this->has_dp=false;
		this->has_d=false;
	}
};

template<class Archive>
void serialize(Archive & ar, particle &v, const unsigned int version) {
	ar & v.mass; ar & v.charge; ar & v.energy; ar & v.phi;
}

template<class Archive>
void serialize(Archive & ar, detectorparams &v, const unsigned int version) {
	ar & v.x0; ar & v.dx; ar & v.N;
	ar & v.dy; ar & v.B;
}

template<class Archive>
void serialize(Archive & ar, detectordata &v, const unsigned int version) {
	ar & v.energy;
	ar & v.points;
}

template<class Archive>
void serialize(Archive & ar, particleguess &v, const unsigned int version) {
	ar & v.mass; ar & v.charge; ar & v.energy; ar & v.phi;
	ar & v.cr; ar & v.cx; ar & v.cy;
}

template<class Archive>
void serialize(Archive & ar, point &v, const unsigned int version) {
	ar & v.x; ar & v.y;
}
