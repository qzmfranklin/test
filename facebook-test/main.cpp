#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>
/******************************************************************************/

struct node_t {
	int n;
	int *a;
};
struct test_t {
	int n;
	int k;
	struct node_t *a;
	//struct {
		//int n;
		//int *a;
	//} *a;
};
int compare_int (const void * a, const void * b);
struct test_t *test_create(int &num_test)
{
	scanf("%d\n",&num_test);
	struct test_t *w=(struct test_t*)malloc(sizeof(struct test_t)*num_test);

	for (int i = 0; i < num_test; i++) {
		scanf("%d %d\n",&(w[i].n),&(w[i].k));
		w[i].a=(struct node_t*)malloc(sizeof(struct node_t)*w[i].n);
		for (int j = 0; j < w[i].n; j++) {
			struct node_t *n=w[i].a+j;
			scanf("%d",&(n->n));
			n->a=(int*)malloc(sizeof(int)*n->n);
			for (int k = 0; k < n->n; k++)
				scanf("%d ",n->a+k);
			qsort(n->a,n->n,sizeof(int),compare_int);
		}
	}

	return w;
}

void test_destory(int &num_test, struct test_t *w)
{
	// lazy now...
}

void test_print(const struct test_t *t)
{
	printf("N=%d K=%d\n",t->n,t->k);
	for (int j = 0; j < t->n; j++) {
		printf("[%5d] ",t->a[j].n);
		for (int k = 0; k < t->a[j].n; k++)
			printf("%3d ",t->a[j].a[k]);
		printf("\n");
	}
}

int compare_int (const void * a, const void * b)
{
	//return ( *(int*)a - *(int*)b ); //increasing order
	return ( *(int*)b - *(int*)a ); //decreasing order
} 

int test_count(const struct test_t *t)
{
	int count=0; 

	printf("K=%d\n",t->k);
	for (int i = 0; i < t->n; i++) {
		int left, right;
		int j, flag;
		flag=0;
		for (j = 0; j < t->a[i].n; j++) {
			int icount=0;
			for (int k = 0; k < t->n; k++) {
				if (i==k) continue;
				int l;
				for (l = 0; l < t->a[k].n; l++)
					if (t->a[i].a[j] < t->a[k].a[l]) break;
				if (l<t->a[k].n)
					icount++;
				//printf("[%d,%d] ",l,icount);
				if (icount == t->k-1) {
					flag = 1;
					break;
				}
			}
			if (flag==1) break;
		}
		left=(flag==1)?j:t->a[i].n;

		flag=0;
		for (j = t->a[i].n-1; j >=0 ; j--) {
			int icount=0;
			for (int k = 0; k < t->n; k++) {
				if (i==k) continue;
				int l;
				for (l = t->a[k].n-1; l >=0 ; l--)
					if (t->a[i].a[j] > t->a[k].a[l]) break;
				if (l<t->a[k].n)
					icount++;
				//printf("[%d,%d] ",l,icount);
				if (icount == t->k-1) {
					flag = 1;
					break;
				}
			}
			if (flag==1) break;
		}
		if (flag==1) left=j;
			//count+=t->a[i].n-j;
		//printf("%d\n",count);
		//printf("\n");
	}

	return count;
}

int main(int argc, char const* argv[])
{ 
	int n;
	struct test_t *w = test_create(n);

	//printf("test 1\n");
	//test_print(w);
	//printf("%d\n",test_count(w));

	//printf("\n\n");

	//printf("test 2\n");
	test_print(w+1);
	printf("%d\n",test_count(w+1));


	return 0;
}
