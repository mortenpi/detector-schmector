class Distribution {
	public:
	Distribution() {}
	virtual double pdf(double x) = 0;
	//virtual double cdf(double x);
	//virtual double invcdf(double x);
};

class NormalDistribution: public Distribution {
	double A, B, mean;
	
	public:
	NormalDistribution(double mean, double stdev);
	double pdf(double x);
};

class ExponentialDistribution: public Distribution {
	double lambda;
	
	public:
	ExponentialDistribution(double lambda);
	double pdf(double x);
	double invcdf(double Fx);
};
