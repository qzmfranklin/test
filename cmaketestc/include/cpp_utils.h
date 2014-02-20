#ifndef _CPP_UTILS_H_
#define _CPP_UTILS_H_
/******************************************************************************/
#include "Table.h"
#include "Random.h"
#include "StatVector.h"
#include "TimeStamp.h"
/******************************************************************************/
//TODO

/*
 * Output a matrix to a file.
 */
void matrix_out(const char* fname, const int m, const int n, double *restrict v,
		int lda=0);

/*
 * Flush an array (either matrix or vector).
 */
void array_flush(double *v, int size);

/*
 * Solves A.x=rhs.
 */
void solve2x2(double *restrict A, double *restrict rhs, double *restrict x);

/*
 * Verify directory (create).
 */
void verify_dir(const char *dir);

/*
 * Link stdout to a file.
 */
void link_stdout(const char *fname);

/*
 * Unlink and restore stdout redirected by link_stdout.
 */
void unlink_stdout();

/*
 * Initialize a vector randomly. Max=10.0.
 */
void init_vector(int n, double* v, int incx=1);

/*
 * Initialize a matrix randomly. Max=10.0.
 */
void init_matrix(int m, int n, double* a, int lda=0);

/*
 * Print a vector to stdout.
 */
void print_vector(const char* desc, const int n, double* v, int incx=1);

/*
 * Print a matrix to stdout.
 */
void print_matrix(const char* desc, const int m, const int n, 
		double *a, int lda=0);
/*
 * Link std::cout to a file.
 */
void link_cout(const char *fname);

/*
 * Unlink and restore std::cout redirected by link_cout.
 */
void unlink_cout();
/******************************************************************************/
#endif