#include <stdio.h>
#include <iostream>

// return the index, return -1 upon failure
template<typename T> 
int binsort(const T &key, const T *a, const int n)
{
	if (n<=0) return -1;
	int i=0, j=n-1, k;
	while (j-i>1) {
		k = (i+j)/2;
		if (a[k]>key)
			j=k;
		else if (a[k]<key)
			i=k;
		else
			return k;
	}
	if (a[i]==key)
		return i;
	if (j>i && a[j]==key)
		return j;
	return -1;
}

int main(int argc, char const* argv[])
{
	const int N=20;
	int a[N];

	for (int i = 0; i < N; i++)
		a[i] = i;

	int index = binsort(3,a,N);
	//printf("index = %d\n",index);

	return 0;
}
