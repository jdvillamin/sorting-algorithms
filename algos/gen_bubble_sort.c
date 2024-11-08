#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void bubble_sort(int a[], int n) {
	int i, j, swapped;
	for (i = 0; i + 1 < n; i++) {
		swapped = 0;
		for (j = 0; j + 1 < n - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				swapped = 1;
			}
		}
		if (!swapped) 
			break;
	}
}

void gen_bubble_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
	int i, j, swapped;
	for (i = 0; i + 1 < n; i++) {
		swapped = 0;
		for (j = 0; j + 1 < n - i; j++) {
			if (cmp(base + (j * size), base + ((j + 1) * size))) {
				gen_swap(base + (j * size), base + ((j + 1) * size), size);
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", gen_brute(gen_bubble_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	gen_bubble_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

