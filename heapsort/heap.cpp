#include <stdio.h>
#include "heap.h"
/******************************************************************************/
static void swp(int &a, int &b);
static void sink_left(const int size, int *a, const int n);
static void sink_right(const int size, int *a, const int n);
/******************************************************************************/
static int swp_count=0;

static void swp(int &a, int &b)
{
	swp_count++;
	printf("\t%3d <-> %3d\n",a,b);
	int c = a;
	a = b;
	b = c;
	return;
}
static void sink_left(const int size, int *a, const int n)
{
	//fprintf(stderr,"sink_left\n");
	if (2*n+1>=size) return;
	if (a[2*n+1]>a[n]) {
		swp(a[2*n+1],a[n]);
		sink_right(size,a,2*n+1);
		sink_left(size,a,2*n+1);
	}
}
static void sink_right(const int size, int *a, const int n)
{
	//fprintf(stderr,"sink_right\n");
	if (2*n+2>=size) return;
	if (a[2*n+2]>a[n]) {
		swp(a[2*n+2],a[n]);
		sink_left(size,a,2*n+2);
		sink_right(size,a,2*n+2);
	}
}
static void crtheap(const int size, int *a)
{ 
	printf("crtheap\n");
	if (size<2) return; 

	int n=size/2;
	while (--n>-1) {
		printf("n = %d\n",n);
		sink_left(size,a,n);
		sink_right(size,a,n);
	}

	return;
}
static void pop(const int size, int *a)
{
	printf("pop\n");

	swp(a[0],a[size-1]);
	sink_right(size-1,a,0);
	sink_left(size-1,a,0);
}
/******************************************************************************/
void heapsort(int size, int *a)
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
