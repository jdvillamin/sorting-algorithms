#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "brute.h"

// implement sorting algorithm here
void bubsort(int a[], int n) {
	int i, j, swapped;
	for (i = 0; i + 1 < n; i++) {
		swapped = 0;
		for (j = 0; j + 1 < n - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				swapped = 1;
			}
		}
		if (!swapped) break;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", brute(bubsort, 10));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	bubsort(a, n);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

