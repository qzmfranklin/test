#ifndef _IML_ITR_H_
#define _IML_ITR_H_

class itr {
	private:
		int status;
		int nitr;
		int error_code;
		double rel_tol;
		double abs_tol
		double rel_err;
		double abs_err;
	public:
	public:
		void breakdown(const int errcode, const char *mesg) {
			error_code = errcode;
			fprintf(stderr,"%s\n",mesg);
		}
		inline bool converged(const double r) {
			if (normb_ == 0)
				return r < atol_;  // ignore relative tolerance if |b| is zero
			resid_ = r / normb_;
			return (resid_ <= rtol_ || r < atol_); // relative or absolute tolerance.
		}

		inline void operator++() { ++i; }
		bool finished(const double r) {
			if (converged(r))
				return true;
			else if (i < max_iter)
				return false;
			else {
				error = 1;
				return true;
			}
		}
};


#endif /* end of include guard */
