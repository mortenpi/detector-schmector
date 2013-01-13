#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "event.hpp"

#include "simulator.hpp"

Simulator::Simulator(ParticleGenerator * pg, Detector * det, Reconstructor * reco, detectorparams dp) {
	this->pg = pg;
	this->det = det;
	this->reco = reco;
	this->dp = dp;
}

void Simulator::run(const char * file, int N) {
	std::ofstream fout(file);
	boost::archive::text_oarchive oa(fout);
	
	for(int i=0; i<N; i++) {
		particle p = this->pg->generate();
		detectordata data = this->det->simulate(p);
		particleguess guess = this->reco->reco(data);
		
		Event ev;
		ev.has_p = true;
		ev.p = p;
		ev.has_d = true;
		ev.d = data;
		ev.has_dp = true;
		ev.dp = this->dp;
		ev.has_g = true;
		ev.g = guess;
		
		oa << ev;
	}
	
	fout.close();
}
