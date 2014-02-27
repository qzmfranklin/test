#include <assert.h>
#include <mkl.h>
#include "Matrix.h"
#include "Vector.h"
/******************************************************************************/
Matrix::Matrix(const unsigned int m_, const unsigned int n_, const double *a_)
{
	assert(m_>0 && n_>0 && a_);
	a=(double*)mkl_malloc(sizeof(double)*m*n,64);
	for (int i = 0; i < m*n; i++)
		a[i] = a_[i];
}
Matrix::~Matrix()
{
	if (!a) mkl_free(a);
}
Vector& Matrix::mult(const Vector &in, Vector &out)const
{
	assert(in.n==n);
	assert(out.n==m);
	for (int i = 0; i < m; i++)
		out.a[i] = 0.0;
	for (int j = 0; j < n; j++)
		for (int i = 0; i < m; i++)
			out.a[i] += in.a[j] * a[i+m*j];
	return out;
}
Vector& Matrix::transmult(const Vector &in, Vector &out)const
{
	assert(in.n==m);
	assert(out.n==n);
	for (int i = 0; i < n; i++)
		out.a[i] = 0.0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			out.a[i] += in.a[j] * a[j+n*i];
	return out;
}
double& Matrix::operator()(const int i, const int j)
{
	assert(i>0 && i<m);
	assert(j>0 && j<n);
	return a[i+j*m];
}
void Matrix::Print()
{
	assert(m>0 && n>0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) 
			printf("%8lf\n",a[i+j*m]);
	printf("\n");
}
