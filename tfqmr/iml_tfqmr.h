/*
 * Copyright (C) 2014 Zhongming Qu <qzmfranklin@gmail.com>
 */

/*
 * =======================================================================
 * Copyright (C) 1997-2001
 * Authors: Andrew Lumsdaine <lums@osl.iu.edu> 
 *          Lie-Quan Lee     <llee@osl.iu.edu>
 * 
 * This file is part of the Iterative Template Library
 * 
 * You should have received a copy of the License Agreement for the
 * Iterative Template Library along with the software;  see the
 * file LICENSE.  
 * 
 * Permission to modify the code and to distribute modified code is
 * granted, provided the text of this NOTICE is retained, a notice that
 * the code was modified is included with the above COPYRIGHT NOTICE and
 * with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
 * file is distributed with the modified code.
 * 
 * LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
 * By way of example, but not limitation, Licensor MAKES NO
 * REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
 * PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
 * OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
 * OR OTHER RIGHTS.
 * =======================================================================
 */

#ifndef _IML_TFQMR_H_
#define _IML_TFQMR_H_

/*
 * : Transpose Free Quasi-Minimal Residual
 * 
 *  Transpose free QMR. First solve Q_1 A Q_2 x = Q_1 b. Then,
 *  return z which is Q_2 x. Here Q1 and Q2 are precondtioners.
 *  Suppose M is about equal to A and M = M_1 * M_2, then
 *  Q_1 = M_1^{-1} and Q_2 = M_2^{-1}
 *  <p>
 *  The residual holds |b - A * x_m| < sqrt{m+1} * tau_m. 
 *  The algorithm check the latter to see if convergence arrives instead of 
 *  checking real residual.
 *  <p>
 * <table align=center border=1>
 * <tr><td> return value </td>   <td>   meaning </td> </tr>
 * <tr><td>      0   </td><td>   convergence within maximum iterations </td> </tr>
 * <tr><td>      1   </td><td>     no convergence after maximum iterations</td> </tr>
 *  <tr><td>     2  </td><td>      breakdown in       tau </td> </tr>
 *  <tr><td>     3  </td><td>      breakdown in       alpha </td> </tr>
 *  <tr><td>     4  </td><td>      breakdown in       gamma</td> </tr>
 *  <tr><td>     5  </td><td>      breakdown in       rho</td> </tr>
 * </table>
 * 
 *  <p>
 *  See: R. W. Freund, A Transpose-Free Quasi-Minimal Residual algorithm for 
 *  non-Hermitian linear system. SIAM J. on Sci. Comp. 14(1993), pp. 470-482
 * 
 * !category: itl,algorithms
 * !component: function
 * !definition: tfqmr.h
 * !tparam: Matrix  - Matrix or multiplier for matrix free methods
 * !tparam: Vector - Vector 
 * !tparam: VectorB - Vector
 * !tparam: Preconditioner -  Incomplete LU, Incomplete LU with threshold, SSOR or identity_preconditioner.
 * !tparam: Iteration - Controls the stopping criteria
 */

/*
 * Required operations:
 * Vector:
 * 	int size() const;
 * 	void set(const double a);
 * 	void copy(const Vector &v);
 * 	void add(const double a, Vector &in, Vector &out);
 * 	double norm2() const;
 * 	double dot(const Vector &v) const;
 * Matrix:
 * 	void mult(Vector &in, Vector &out) const;
 * Precond1, Precond2:
 * 	void solve(Vector &in, Vector &out) const;
 */

template <class Vector, class Matrix, class Precond1, class Precond2>
int tfqmr(const Matrix& A, Vector& x, const Vector& b, const Precond1& M1, const Precond2& M2);

#endif
