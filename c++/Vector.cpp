#include "Vector.h"
#include <stdio.h>
#include <assert.h>
#include <mkl.h>
#include <math.h>
/******************************************************************************/
Vector::Vector()
{
	n=0;
	a=0;
}
Vector::Vector(unsigned int n_)
{
	n=n_; 
	a=(double*)mkl_malloc(sizeof(double)*n_,64);
	assert(a);
}
Vector::~Vector()
{
	if (!a) mkl_free(a);
}
/******************************************************************************/
Vector& Vector::operator=(const Vector &v)
{
	if (this!=&v) { 
		n=v.n;
		if (!(v.a)) 
			a=v.a;
		else 
			a=(double*)mkl_malloc(sizeof(double)*n,64);
		assert(a);
		for (int i = 0; i < n; i++)
			a[i] = v.a[i];
	}
	return *this;
}
Vector& Vector::operator=(const double val)
{
	for (int i = 0; i < n; i++)
		a[i]=val;
	return *this;
}
Vector& Vector::operator+=(const Vector &v)
{
	assert(v.n && v.n==n);
	for (int i = 0; i < n; i++)
		a[i] += v.a[i];
	return *this;
}
Vector& Vector::operator-=(const Vector &v)
{
	assert(v.n && v.n==n);
	for (int i = 0; i < n; i++)
		a[i] -= v.a[i];
	return *this;
}
Vector& Vector::operator+=(const double val)
{
	for (int i = 0; i < n; i++)
		a[i] += val;
	return *this;
}
Vector& Vector::operator-=(const double val)
{
	for (int i = 0; i < n; i++)
		a[i] -= val;
	return *this;
}
Vector& Vector::operator*=(const double val)
{
	for (int i = 0; i < n; i++)
		a[i] *= val;
	return *this;
}
double& Vector::operator()(const int i)
{
	assert(i>=0&&i<n);
	return a[i];
}
double& Vector::operator[](const int i)
{
	assert(i>=0&&i<n);
	return a[i];
}
/******************************************************************************/
double Vector::norm()const
{
	double tmp=0.0;
	for (int i = 0; i < n; i++)
		tmp += a[i] * a[i];
	return sqrt(tmp);
}
void Vector::Print()
{
	for (int i = 0; i < n; i++)
		printf("%8.f ",a[i]);
	printf("\n");
}
/******************************************************************************/
double dot(const Vector &u, const Vector &v)
{
	double tmp=0.0;
	if (u.n==v.n && v.n!=0)
		for (int i = 0; i < u.n; i++)
			tmp += u.a[i] * v.a[i];
	return tmp;
}
double norm(const Vector &v)
{
	double tmp=0.0;
	for (int i = 0; i < v.n; i++)
		tmp += v.a[i] * v.a[i];
	return sqrt(tmp);
}
