#include <iostream>
#include <cstdlib>
#include <algorithm>

template <typename T> void printArray(T *array, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T> void quickSort(T *array, size_t left, size_t right)
{
	size_t l = left;
	size_t r = right - 1;
	size_t size = right - left;

	if (size > 1) {
		T pivot = array[rand() % size + l];

		while (l < r) {
			while (array[r] > pivot && r > l)
				r--;

			while (array[l] < pivot && l <= r)
				l++;

			if (l < r) {
				std::swap(array[l], array[r]);
				l++;
			}
		}

		quickSort(array, left, l);
		quickSort(array, r, right);
	}
}

int main(void)
{
	size_t size = 1000000;
	int *array = new int[size];

	for (int i = 0; i < size; ++i)
		array[i] = (100.0 * rand()) / RAND_MAX;

	//printArray(array, size);
	quickSort(array, 0, size);
	//printArray(array, size);

	delete [] array;

	return 0;
}


void quickSort_d(double *array, size_t left, size_t right)
{
	size_t l = left;
	size_t r = right - 1;
	size_t size = right - left;

	if (size > 1) {
		double pivot = array[rand() % size + l];

		while (l < r) {
			while (array[r] > pivot && r > l)
				r--;

			while (array[l] < pivot && l <= r)
				l++;

			if (l < r) {
				std::swap(array[l], array[r]);
				l++;
			}
		}

		quickSort(array, left, l);
		quickSort(array, r, right);
	}
}

//int main(void)
//{
	//size_t size = 500000;
	//double *array = new double[size];

	//for (int i = 0; i < size; i++)
		//array[i] = (100.0 * rand()) / RAND_MAX;

	//quickSort(array, 0, size);

	//delete [] array;

	//return 0;
//}
