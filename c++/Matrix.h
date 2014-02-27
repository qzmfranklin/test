#ifndef _MATRIX_H_
#define _MATRIX_H_
/******************************************************************************/
class Vector;
class Matrix {
	private:
		unsigned int m,n;
		double *a;
	public:
		/* 
		 * Assume colum-major storage, allocate new space and copy
		 * content in a.
		 */
		Matrix(const unsigned int m, const unsigned int n, const double *a);
		~Matrix();

		Vector& mult(const Vector &in, Vector &out)const;
		Vector& transmult(const Vector &in, Vector &out)const;
		double& operator()(const int m, const int n);

		void Print();
};
/******************************************************************************/
#endif
