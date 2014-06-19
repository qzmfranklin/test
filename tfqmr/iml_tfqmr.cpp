#include "iml_tfqmr.h"

template <class Vector, class Matrix, class Precond1, class Precond2>
int tfqmr(const Matrix& A, Vector& x, const Vector& b, const Precond1& M1, const Precond2& M2)
{
	Vector r0(x.size()),v(x.size());
	Vector tmp(x.size());
	Vector tmp1(x.size());

	//x is initial value

	// 1. r0 = Q1 (b - A Q2 x)
	r0.copy(M2.solve(x));	//r0=M2^{-1}.x
	A.mult(r0,tmp);		//tmp=A.r0
	b.add(-1.0,tmp,tmp);	//tmp=b-tmp
	M1.solve(tmp,r0);	//r0=M1^{-1}.tmp

	// 2. w=y=r
	// 2. w=y=r0?
	Vector w(x.size()),y1(x.size());
	w.copy(r0);
	y1.copy(r0);

	// 3. g=v=Q1.A.Q2.y
	M2.solve(y1,v);
	A.mult(v,tmp);
	M1.solve(tmp,v);

	Vector g(x.size());
	g.copy(v);

	// 4. d=0
	Vector d(x.size());
	d.set(0.0); // set all elements to 0.0

	// 5. tau=||r||2
	double tau = r0.norm2();

	// 6. theta=eta=0
	double theta = 0.0;
	double eta = 0.0;

	// 7. rtilde=r
	Vector rtilde(x.size());
	rtilde.copy(r0);

	// 8. rho=dot(rtilde,r)
	double rho  = tau*tau; // note: tau=r0.norm2()
	double rho0 = rho;

	//Vector y0(size(x));
	double sigma, alpha, c, kappa, beta;
	Vector y0(x.size()),h(x.size());
	while(1) {
		// 9. 10. 11.
		// sigma=dot(rtilde,v)
		// alpha=rho/sigma 
		// y2k=y(2k-1)-alpha*v

		// 9. sigma=dot(rtilde,v)
		sigma = rtilde.dot(v);

		// 10. alpha=rho/sigma
		if (sigma==0.) { iter.breakdown(5, "tfqmr breakdown: sigma=0"); break; }
		alpha = rho / sigma;

		// 11. y2k=y(2k-1)-alpha*v
		// y0 = y1 - alpha * v;
		y1.add(-alpha,v,y0);

		// 12. h=Q1*A*Q2*y
		M2.solve(y0,h);
		A.mult(h,tmp);
		M1.solve(tmp,h);

		//split the loop of "for m = 2k-1, 2k" 

		/**************************************/
		//The first one

		// 13. w=w-alpha*Q1AQ2y0
		// w = w - alpha * g;
		w.add(-alpha,g,w);

		// 18. d=y0+((theta0^2)*eta0/alpha)*d         //need check breakdown
		// d = y1 + ( theta * theta * eta / alpha ) * d;
		if (alpha==0.) { iter.breakdown(3, "tfqmr breakdown: alpha=0"); break; }
		y1.add(theta*theta*eta/alpha,d,d);

		// 14. theta=||w||_2/tau0       //need check breakdown
		if (tau==0.) { iter.breakdown(2, "tfqmr breakdown: tau=0"); break; }
		theta=w.norm2()/tau; // tau is not updated yet

		// 15. c=1/sqrt(1+theta^2)
		c=1.0/sqrt(1.0+theta*theta);

		// 16. tau=tau0*theta*c
		tau = tau * c * theta;

		// 17.  eta=(c^2)*alpha
		eta = c * c * alpha;

		// 19. x=x+eta*d
		x.add(eta,d,x);

		// 20. kappa=tau*sqrt(m+1)
		kappa = tau * sqrt( 2.* (iter.iterations()+1) );

		// 21. check stopping criterion
		if ( iter.finished(kappa) ) {
			//before return, transform x to the solution of Ax = b
			solve(M2, x, tmp);
			itl::copy(tmp, x);
			break;
		}
		//g = h;
		g.copy(h);

		/**************************************/
		//The second one

		// 13. w=w-alpha*Q1AQ2y0
		// w = w - alpha * g;
		w.add(-alpha,g,w);

		// 18. d=y0+((theta0^2)*eta0/alpha)*d
		// d = y0 + ( theta * theta * eta / alpha ) * d;
		if (alpha==0.) { iter.breakdown(3,"tfqmr breakdown: alpha=0"); break; }
		y0.add(theta*theta*eta/alpha,d,d);

		// 14. theta=||w||_2/tau0
		if (tau==0.) { iter.breakdown(2, "tfqmr breakdown: tau=0"); break; }
		//theta = itl::two_norm(w) / tau;
		theta = w.norm2()/tau;

		// 15. c=1/sqrt(1+theta^2)
		c = 1.0 / sqrt(1.0 + theta * theta);

		// 16. tau=tau0*theta*c
		tau = tau * c * theta;

		// 17.  eta=(c^2)*alpha
		eta = c * c * alpha;

		// 19. x=x+eta*d
		x.add(eta,d,x);

		// 20. kappa=tau*sqrt(m+1)
		kappa = tau * sqrt(2.* (iter.iterations()+1)  + 1.);

		// 21. check stopping criterion
		if ( iter.finished(kappa) ) {
			itl::solve(M2, x, tmp);
			itl::copy(tmp, x);
			break;
		}    

		// 22. rho=dot(rtilde,w)
		// 23. beta=rho/rho0                     //need check breakdown

		rho0 = rho;
		//rho = itl::dot(rtilde, w);
		rho  = rtilde.dot(w);
		if (rho0==0.) { iter.breakdown(4, "tfqmr breakdown: beta=0"); break; }
		beta=rho/rho0;

		// 24. y=w+beta*y0
		// y1 = w + beta * y0;
		w.add(beta,y0,y1);

		// 25. g=Q1.A.Q2.y
		// g = Q1 * ( A * ( Q2 * y1) );
		M2.solve(y1,g);
		A.mult(g,tmp);
		M1.solve(tmp,g);

		// 26. v=Q1AQ2y+beta*(Q1AQ2y0+beta*v)
		// v = g + beta * ( h + beta * v );
		h.add(beta,v,tmp);
		g.add(beta,tmp,v);

		++iter;
	}

	return iter.error_code();
}
