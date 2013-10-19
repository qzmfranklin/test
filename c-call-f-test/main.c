#include <stdio.h>
#include <complex.h>

int main(int argc, const char *argv[])
{
	/*int i,j,result;*/
	/*i=100;*/
	/*j=203;*/
	/*add(&i, &j, &result);*/
	/*printf("%4d+%4d=%4d\n",i,j,result);*/
	/*take(&i, &j, &result);*/
	/*printf("%4d-%4d=%4d\n",i,j,result);*/

	/*double complex x=1.0+3.0*I;*/
	/*double complex y=-1.9+2.9*I;*/
	/*double complex z=0.0+0.0*I;*/
	/*printf("x=%5.2f+%5.2f*I\n",creal(x),cimag(x));*/
	/*printf("y=%5.2f+%5.2f*I\n",creal(y),cimag(y));*/
	/*add_c(&x,&y,&z);*/
	/*printf("x+y=%5.2f+%5.2f*I\n",creal(z),cimag(z));*/
	/*take_c(&x,&y,&z);*/
	/*printf("x+y=%5.2f+%5.2f*I\n",creal(z),cimag(z));*/

	/*double a[3]={1.0,3.9,9.3};*/
	/*double b[3]={-2.0,0.9,-6.4};*/
	/*double c=0.0;*/
	/*printf("a={%5.2f,%5.2f,%5.2f}\n",a[0],a[1],a[2]);*/
	/*printf("b={%5.2f,%5.2f,%5.2f}\n",b[0],b[1],b[2]);*/
	/*dot(a,b,&c);*/
	/*printf("a.b=%5.2f\n",c);*/

	double complex x[3]={1.2+0.2*I,-1.9-3.5*I,0.0+0.9I};
	double complex y[3]={-2.1+2.2*I,1.4+1.5*I,4.2-1.9I};
	double complex z;
	printf("x={%5.2f+%5.2f*I,%5.2f+%5.2f*I,%5.2f+%5.2f*I}\n",creal(x[0]),cimag(x[0]),creal(x[1]),cimag(x[1]),creal(x[2]),cimag(x[2]));
	printf("y={%5.2f+%5.2f*I,%5.2f+%5.2f*I,%5.2f+%5.2f*I}\n",creal(y[0]),cimag(y[0]),creal(y[1]),cimag(y[1]),creal(y[2]),cimag(y[2]));
	dot_c(x,y,&z);
	printf("x.y=%5.2f+%5.2f*I\n",creal(z),cimag(z));

	return 0;
}
