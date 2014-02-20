#include <stdio.h>
#include <math.h>
#include <mkl.h>
/*******************************************************************************/
int main(int argc, char const* argv[]);
int test01(void);
int test02(void);
int test03(void);
void init_vector( double *v, int n, int incx=1 );
void init_matrix( double *a, int m, int n, int lda );
void print_vector( double *a, int n, int incx=1 );
void print_matrix( double *a, int m, int n, int lda );

/*******************************************************************************/
int main(int argc, char const* argv[])
{

	test01();
	test02();
	test03();


	return 0;
} 

int test01(void) {
	int err=0; 
        printf("TEST01\n");
        printf("	|Test MKL_TYPES.H\n"); 
	printf("int		= %lu\n",sizeof(int));
	printf("MKL_INT		= %lu\n",sizeof(MKL_INT));
	printf("MKL_INT64	= %lu\n",sizeof(MKL_INT64));
	printf("MKL_Complex8	= %lu\n",sizeof(MKL_Complex8));
	printf("MKL_Complex16	= %lu\n",sizeof(MKL_Complex16)); 
        printf("END OF TEST01\n");
        printf("\n");
	return err;
}

int test02(void) { 
	int err=0; 
        printf("TEST02\n");
        printf("	|Test ddot\n"); 

	double x[5];
	double y[5];
	int n=5; 
	int incx=1;
	int i;
	for (i = 0; i < 5; i++) {
		x[i] = 5.0 * rand()/RAND_MAX;
		y[i] = 5.0 * rand()/RAND_MAX;
	} 
	printf("x=  ");
	print_vector(x,n);
	printf("y=  ");
	print_vector(y,n); 
	double res;
	res = ddot(&n,x,&incx,y,&incx);
	printf("res = x*y = %lf\n",res);

        printf("END OF TEST02\n");
        printf("\n");
	return err; 
}

int test03( void ) {
	int err=0; 
        printf("TEST05\n");
        printf("	|Test dgemm\n");


#define M 5
#define N 3
#define K 4
	double a[M*K], b[K*N], c[M*N];
	int m, n, k, lda, ldb, ldc; 
	char transa, transb;
	double alpha, beta;
	transa	= 'N';
	transb	= 'N';
	m	= M;
	n	= N;
	k	= K;
	lda	= m;
	ldb	= k;
	ldc	= m;
	alpha	= 1.0;
	beta	= 1.0;
	init_matrix( a, m, k, lda );
	init_matrix( b, k, n, ldb );
	init_matrix( c, m, n, ldc );

#undef M
#undef N
#undef K
	printf("a = \n");
	print_matrix( a, m, k, lda );
	printf("b = \n");
	print_matrix( b, k, n, ldb );
	printf("c = \n");
	print_matrix( c, m, n, ldc );
	printf("alpha=%lf\n",alpha);
	printf("beta=%lf\n",beta); 

	dgemm( &transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc );

	printf("alpha*(a.b)+beta*c= \n");
	print_matrix( c, m, n, ldc );
	
        printf("END OF TEST05\n");
        printf("\n");
	return err;
}

void init_vector( double *v, int n, int incx ) {
	int i;
	for (i = 0; i < n; i++)
		v[i*incx] = 5.0 * rand()/RAND_MAX;
}

void init_matrix( double *a, int m, int n, int lda ) {
	int i,j;
	for (j = 0; j < n; j++)
		for (i = 0; i < m; i++)
			a[i+j*lda] = 5.0 * rand()/RAND_MAX;
}

void print_vector( double *a, int n, int incx ) {
	int i;
	for (i = 0; i < n; i++) 
		printf("%8lf  ",a[i*incx]);
	printf("\n");
}

void print_matrix( double *a, int m, int n, int lda ) {
	int i, j;
	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++)
			printf("%8lf  ",a[i+j*lda]);
		printf("\n");
	}
} 
