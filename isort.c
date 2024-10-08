#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void isort(int a[], int n) {
	int i, j;

	for (i = 1; i < n; i++)
		for (j = i; j > 0; j--)
			if (a[j - 1] > a[j])
				swap(&a[j - 1], &a[j]);
			else break;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}
	
	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc == 4) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	isort(a, n);
	t2 = clock();

	check(a, n);
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

