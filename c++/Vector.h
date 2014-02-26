#ifndef _VECTOR_H_
#define _VECTOR_H_
/******************************************************************************/
class Vector {
	private: 
		unsigned int n;
		double *a;
	public:
		Vector();
		Vector(unsigned int n_);
		~Vector();
		Vector& operator=(const Vector &v);
		Vector& operator=(const double val);
		Vector operator+(const Vector &v);
		Vector operator-(const Vector &v);
		Vector operator*(const double val);
		double& operator()(const int i);
		double& operator[](const int i);

		void Print();
};
/******************************************************************************/
#endif
