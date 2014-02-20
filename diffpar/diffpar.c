#include <stdio.h>
#include <math.h>
/******************************************************************************/
void print_diffmat(const int n, const double *a, const double shift);
void get_diff(const int n, const double *a, const double diff, double *val, int *pos);
/******************************************************************************/
int main(int argc, char *argv[])
{
	const int N=8;
	const double a[]={0.0,27.2,30.1,97.9,102.4,190.9,200.5,210.3};

	print_diffmat(N,a,0.0);

	double diff;
	printf("Enter the float number you wish to search:\n");
	scanf("%lf",&diff);

	print_diffmat(N,a,diff);
	/*printf("diff_par = %8.1f\n",diff_par);*/

	int pos[2];
	double val;
	get_diff(N,a,diff,&val,pos);
	printf("  [%4d,%4d](%8.1lf)\n",pos[0],pos[1],val);

	return 0;
} 

void print_diffmat(const int n, const double *a, const double shift)
{
	printf("Diff matrix:\n");
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < i; j++)
			printf("         ");
		for (int j = i+1; j < n; j++)
			printf("%-8.1f ",a[j]-a[i]-shift);
		printf("\n");
	}
} 

/**************************************/
static void cmp(double *val, int *pos, double d, int i, int j)
{
	if (fabs(d)<fabs(*val)) {
		*val = d;
		pos[0] = i;
		pos[1] = j;
	}
}

void get_diff(const int n, const double *a, const double diff, double *val, int *pos)
{
	int num_step=1;

	int i=0,j=1;
	double d = a[1] - a[0] - diff;
	*val = d;
	pos[0] = 0;
	pos[1] = 1;
	printf("  [%4d,%4d](%8.1f)\n",i,j,d);
	while(1) {
		if (d<0.0) {
			if (j==n-1) break;
			j++;
		} else if (d>0.0 && j-i==1) {
			if (j==n-1) break;
			i++;
			j++;
		}
		else {
			if (i==n-2) break;
			i++;
		}
		d = a[j] - a[i] - diff;
		printf("=>[%4d,%4d](%8.1f)\n",i,j,d);
		cmp(val,pos,d,i,j);
		num_step++;
	}
	printf("num_step = %d\n",num_step);
}
