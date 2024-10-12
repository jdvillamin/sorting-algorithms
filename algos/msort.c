#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void merge(int a[], int n) {
	int i, j, k, mid = n / 2, temp[n];

	for (i = 0, j = mid, k = 0; k < n; k++)
		temp[k] = (j >= n || i < mid && a[i] < a[j]) ? a[i++] : a[j++];
	
	memcpy(a, temp, n * sizeof(int));
}

void msort(int a[], int n) {
	if (n > 1) {
		msort(a, n / 2);
		msort(&a[n / 2], n - n / 2);
		merge(a, n);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}
	
	printf("brute result: %d\n", brute(msort, 10));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : time(NULL);

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	msort(a, n);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

