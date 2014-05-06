#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <mkl.h>
#include "iml_tfqmr.h"

class Vector {
	private:
		int size;
		double *data;
	public:
		Vector(const int n): size(n) {
			data = (double*)mkl_malloc(sizeof(double)*n,64);
			assert(data);
		}
		~Vector() { mkl_free(data); }

		void randomize() {
			for (int i = 0; i < size ; i++)
				data[i] = 10.0*rand()/RAND_MAX;
		}

		int size() const { return size; };
		void set(const double a) {
			for (int i = 0; i < size; i++)
				data[i] = a;
		}
		void copy(const Vector &v) {
			for (int i = 0; i < size; i++)
				data[i] = v.data[i];
		}
		void add(const double a, Vector &in, Vector &out) {
			for (int i = 0; i < size; i++)
				out.data[i] = data[i] + a * in.data[i];
		}
		double norm2() const {
			double s=0.0;
			for (int i = 0; i < size; i++)
				s += data[i] * data[i];
			return sqrt(s);
		}
		double dot(const Vector &v) const {
			double s=0.0;
			for (int i = 0; i < size; i++)
				s += data[i] * v.data[i];
			return s;
		}
};

class Matrix {
	private:
		int size;
		double *data;
	public:
		Matrix(const int n): size(n) {
			data = (double*)mkl_malloc(sizeof(double)*n*n,64);
			assert(data);
		}
		~Matrix() { mkl_free(data); }

		void randomize() {
			for (int i = 0; i < size*size ; i++)
				data[i] = 10.0*rand()/RAND_MAX;
		}

		void mult(Vector &in, Vector &out) const {
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					out.data[i] = data[i+j*size] * in.data[j];
		}
};

class Precond {
	public:
		Precond() {}
		~Precond() {}
		void solve(Vector &in, Vector &out) const { return; }
};

int test01(void)
{
	int err=0; 
        printf("TEST01\n");
        printf("	|Test iml_tfqmr\n");

	const int N=500;
	Vector x(N),b(N);
	x.set(1.0);

	Matrix A(N);
	A.randomize();

	A.mult(x,b);
	x.randomize();

	Precond M1,M2;

	tfqmr(A,x,b,M1,M2);

        printf("END OF TEST01\n");
        printf("\n");
	return err;
}

int main(int argc, char const* argv[])
{
	test01();
	return 0;
}
