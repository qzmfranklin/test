#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/******************************************************************************/ 
int main(int argc, char const* argv[])
{
	//const int N=5;
	//int a[N]={1,11,31,41,51};

	int N;
	scanf("%d\n",&N);

	int *a=(int*)malloc(sizeof(int)*N);
	assert(a);

	for (int i = 0; i < N; i++)
		scanf("%d",a+i);

	// assuming first and last elements are not missing
	int comdiff=(a[N-1]-a[0])/N; // common difference
	int trueval=a[0]+comdiff; // expected value
	int ptr=1; // index pointer
	while (a[ptr]==trueval) {
		trueval += comdiff;
		ptr++;
	}

	printf("%d\n",trueval);

	free(a);



	return 0;
}
