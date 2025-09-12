#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 30

int a[N];

void gen_random(int upper_bound,int lower_bound)
{
	int i;
	for (i = 0; i < N; i++)
       a[i] = lower_bound + rand() % (upper_bound - lower_bound);
}

void print_random()
{
	int i;
	for (i = 0; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(void)
{
	gen_random(20,10);
	print_random();
	return 0;
}
