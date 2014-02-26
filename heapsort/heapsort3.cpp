#include <stdio.h>
#include "heapsort3.h"
/******************************************************************************/
static void swp(int *a, int *b);
static void sink(const int size, int *a, const int n);
/******************************************************************************/
static int swp_count=0;

static void swp(int *a, int *b)
{
	swp_count++;
	printf("\t%3d <-> %3d\n",*a,*b);
	int c = *a;
	*a = *b;
	*b = c;
	return;
}
static void sink(const int size, int *a, const int n)
{
	//fprintf(stderr,"sink\n");
	if (3*n+1>=size)
		return;
	else if (3*n+2==size) {
		if (a[3*n+1]>a[n]) {
			swp(a+3*n+1,a+n);
			sink(size,a,3*n+1); 
		}
	} else if (3*n+3==size) {
		if (a[3*n+1]>a[n] && a[3*n+1]>a[3*n+2]) {
			swp(a+3*n+1,a+n);
			sink(size,a,3*n+1);
		} else if (a[3*n+2]>a[n] && a[3*n+2]>a[3*n+1]) {
			swp(a+3*n+2,a+n);
			sink(size,a,3*n+2);
		} 
	} else { 
		if (a[3*n+1]>a[n] && a[3*n+1]>a[3*n+2] && a[3*n+1]>a[3*n+3]) {
			swp(a+3*n+1,a+n);
			sink(size,a,3*n+1);
		} else if (a[3*n+2]>a[n] && a[3*n+2]>a[3*n+1] && a[3*n+2]>a[3*n+3]) {
			swp(a+3*n+2,a+n);
			sink(size,a,3*n+2);
		} else if (a[3*n+3]>a[n] && a[3*n+3]>a[3*n+1] && a[3*n+3]>a[3*n+2]) {
			swp(a+3*n+3,a+n);
			sink(size,a,3*n+3);
		}
	}
}
static void crtheap(const int size, int *a)
{ 
	printf("crtheap\n");
	if (size<2) return; 

	int n=size/3;
	while (--n>-1) {
		printf("n = %d\n",n);
		sink(size,a,n);
	}

	return;
}
static void pop(const int size, int *a)
{
	printf("pop\n");

	swp(a,a+size-1);
	sink(size-1,a,0);
}
/******************************************************************************/
void heapsort3(int size, int *a)
{
	fprintf(stderr,"heapsort\n");

	if (!size) return;

	swp_count=0;

	crtheap(size,a); 

	do
		pop(size,a);
	while (--size>0);

	printf("swp_count=%d\n",swp_count);

	return;
}
