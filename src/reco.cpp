#include <gsl/gsl_multimin.h>
#include <gsl/gsl_linalg.h>
#include <cstdio>

#include "reco.hpp"

Reconstructor::Reconstructor(detectorparams param) {
	this->params = param;
}

LSFCircleReco::LSFCircleReco(detectorparams param) : Reconstructor(param) {}

// Least squares with GSL Multidimensional minimizer
double * vec_x; double * vec_y; int N;

inline double res2i(double x, double y, int i) {
	double r = sqrt(x*x + y*y);
	double dx = x - vec_x[i];
	double dy = y - vec_y[i];
	double resi = sqrt(dx*dx + dy*dy) - sqrt(x*x + y*y);
	return resi*resi;
}

inline double sum_res2(double x, double y) {
	double res2 = 0;
	for(int i=0; i<N; i++) {
		res2 += res2i(x,y,i);
		//printf("%d: %f\n", i, res2);
	}
	return res2;
}

double minif(const gsl_vector * v, void * params) {
	double x, y;
	//double *p = (double *)params;

	x = gsl_vector_get(v, 0);
	y = gsl_vector_get(v, 1);

	return sum_res2(x,y);
}

particleguess LSFCircleReco::reco(detectordata d) {
	particleguess ret;
	
	N = d.points.size();
	vec_x = new double[N];
	vec_y = new double[N];
	for(int i=0; i<N; i++) {
		vec_x[i] = d.points[i].x;
		vec_y[i] = d.points[i].y;
	}
	
	printf("Best: %f\n", sum_res2(0, -2.23));
	
	// GSL code
	const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
	gsl_multimin_fminimizer *s = NULL;
	gsl_vector *ss, *x;
	gsl_multimin_function minex_func;

	/* Starting point */
	x = gsl_vector_alloc (2);
	gsl_vector_set (x, 0, 0.0);
	gsl_vector_set (x, 1, -2.0);

	/* Set initial step sizes */
	ss = gsl_vector_alloc (2);
	gsl_vector_set_all (ss, 0.1);

	/* Initialize method and iterate */
	minex_func.n = 2;
	minex_func.f = minif;
	minex_func.params = NULL;

	s = gsl_multimin_fminimizer_alloc (T, 2);
	gsl_multimin_fminimizer_set (s, &minex_func, x, ss);

	size_t iter = 0;
	int status;
	double size;

	do {
		iter++;
		status = gsl_multimin_fminimizer_iterate(s);

		if (status) break;

		size = gsl_multimin_fminimizer_size (s);
		status = gsl_multimin_test_size (size, 1e-2);

		if (status == GSL_SUCCESS) {
			printf ("converged to minimum at\n");
		}

		printf ("%5d %10.3e %10.3e f() = %7.3f size = %.3f\n", 
			iter,
			gsl_vector_get (s->x, 0), 
			gsl_vector_get (s->x, 1), 
			s->fval, size
		);
	}
	while (status == GSL_CONTINUE && iter < 1000);

	gsl_vector_free(x);
	gsl_vector_free(ss);
	gsl_multimin_fminimizer_free (s);
	
	// Done
	delete vec_x, vec_y;
	
	return ret;
}

SimpleLSFCircleReco::SimpleLSFCircleReco(detectorparams param) : Reconstructor(param) {}

particleguess SimpleLSFCircleReco::reco(detectordata d) {
	particleguess ret;
	
	int N = d.points.size();
	double A_data[] = {0,0,0,0,0,0,0,0,N};
	double B_data[] = {0,0,0};
	for(int i=0; i<N; i++) {
		double xi = d.points[i].x;
		double yi = d.points[i].y;
		
		A_data[0] += xi*xi;
		A_data[1] += xi*yi;
		A_data[2] += xi;
		A_data[3] += xi*yi;
		A_data[4] += yi*yi;
		A_data[5] += yi;
		A_data[6] += xi;
		A_data[7] += yi;
		
		B_data[0] += xi*(xi*xi + yi*yi);
		B_data[1] += yi*(xi*xi + yi*yi);
		B_data[2] += xi*xi + yi*yi;
	}
	
	gsl_matrix_view A = gsl_matrix_view_array(A_data, 3, 3);
	gsl_vector_view b = gsl_vector_view_array(B_data, 3);
	gsl_vector *x = gsl_vector_alloc(3);

	int s;
	gsl_permutation * p = gsl_permutation_alloc(3);
	gsl_linalg_LU_decomp (&A.matrix, p, &s);
	gsl_linalg_LU_solve (&A.matrix, p, &b.vector, x);

	double Xa = gsl_vector_get(x, 0);
	double Xb = gsl_vector_get(x, 1);
	double Xc = gsl_vector_get(x, 2);

	gsl_permutation_free(p);
	gsl_vector_free(x);
	
	ret.cx = (-1)*Xa/2;
	ret.cy = (-1)*Xb/2;
	ret.cr = sqrt(4*Xc + Xa*Xa + Xb*Xb)/2;
	
	return ret;
}
