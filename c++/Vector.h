#ifndef _VECTOR_H_
#define _VECTOR_H_
/******************************************************************************/
class Matrix;
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

		Vector& operator+=(const Vector &v);
		Vector& operator-=(const Vector &v);
		Vector& operator+=(const double val);
		Vector& operator-=(const double val);
		Vector& operator*=(const double val);

		double& operator()(const int i);
		double& operator[](const int i);

		double norm()const;
		void Print();

		friend Vector& add(const Vector &u, const Vector &v, Vector &res);
		friend Vector& sub(const Vector &u, const Vector &v, Vector &res);
		friend Vector& mul(const Vector &u, const Vector &v, Vector &res);
		friend Vector& mul(const Vector &u, const double val, Vector &res);

		friend double dot(const Vector &u, const Vector &v);
		friend double norm(const Vector &u); 
		friend class Matrix;
};
/******************************************************************************/
#endif
