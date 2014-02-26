#include "Vector.h"
#include <stdio.h>
#include <assert.h>
#include <mkl.h>
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
	//printf("a\t=%p\n",a);
	for (int i = 0; i < n; i++)
		a[i]=10.0;

	//for (int i = 0; i < n; i++)
		//printf("%8f ",a[i]);
	//printf("\n");
}
Vector::~Vector()
{
	if (!a) mkl_free(a);
}
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
Vector Vector::operator+(const Vector& v)
{
	if (v.a)
		for (int i = 0; i < n; i++)
			a[i]+=v.a[i];
	return *this;
}
Vector Vector::operator-(const Vector& v)
{
	if (v.a)
		for (int i = 0; i < n; i++)
			a[i]-=v.a[i];
	return *this;
}
Vector Vector::operator*(const double val)
{
	for (int i = 0; i < n; i++)
		a[i]*=val;
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
void Vector::Print()
{
	for (int i = 0; i < n; i++)
		printf("%8f ",a[i]);
	printf("\n");
}
