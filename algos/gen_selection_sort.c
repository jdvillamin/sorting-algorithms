#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void selection_sort(int a[], int n) {
	int i, j, min_idx;
	for (i = 0; i < n; i++) {
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min_idx])
				min_idx = j;
		swap(&a[i], &a[min_idx]);
	}
}

void gen_selection_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
	int i, j, min_idx;
	for (i = 0; i < n; i++) {
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (cmp(base + (min_idx * size), base + (j * size)))
				min_idx = j;
		gen_swap(base + (i * size), base + (min_idx * size), size);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", gen_brute(gen_selection_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	gen_selection_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

