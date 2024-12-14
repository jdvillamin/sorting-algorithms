#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void merge(int a[], int n) {
	int i, j, k, mid = n / 2, temp[n];

	for (i = 0, j = mid, k = 0; k < n; k++)
		temp[k] = (j == n || i < mid && a[i] < a[j]) ? a[i++] : a[j++];
	
	memcpy(a, temp, n * sizeof(int));
}

void merge_sort(int a[], int n) {
	if (n > 1) {
		merge_sort(a, n / 2);
		merge_sort(&a[n / 2], n - n / 2);
		merge(a, n);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}

	if (!brute(merge_sort)) {
		fprintf(stderr, "Failed brute force verification\n");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc == 4) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	merge_sort(a, n);
	t2 = clock();

	if (!check(a, n)) {
		fprintf(stderr, "Failed main input case check\n");
		exit(1);
	}

	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
