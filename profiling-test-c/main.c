#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MY_SIZE 100000

int main(int argc, char *argv[])
{
    double x[MY_SIZE], y[MY_SIZE], z[MY_SIZE], b[MY_SIZE], avg = 0.0;
    int i, count;

    count = MY_SIZE;
    if (argc > 1)
        count = atoi(argv[1]);
    printf("num args = %d, count = %d\n", argc, count);
    for (i = 0; i < MY_SIZE; i++)
    {
        x[i] = rand();
        y[i] = rand();
        z[i] = rand();
    }
    for (i = 0; i < count; i++)
        b[i] = x[i] * y[i] + z[i];
    printf("average = %lf\n", avg);
    for (i = 0; i < count; i++)
        avg = b[i] / count;
    printf("average = %lf\n", avg);
    return 0;
}
