#include "stdio.h"
#include "mathlink.h"

double fun(double);

void addtwo(void){
  	double i,j,sum;
  	MLGetReal(stdlink,&i);
  	MLGetReal(stdlink,&j);
	sum=i+j;
	int counter;
	double *res=(double*)malloc(10*sizeof(double));
	for ( counter = 0; counter < 10; counter++) {
		res[counter]=sum+fun((double)counter); 
	}
	int dim[]={2,5};
	int d=2;
	/*MLPutReal64List(stdlink,res,10); */
	MLPutReal64Array(stdlink,res,dim, NULL, d);
}

double fun(double a){
	return a*a;
}

int main(int argc, char *argv[])
{
	return MLMain(argc,argv);
}
