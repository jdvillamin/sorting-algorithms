#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

/*
 * Use insertion sort, but preprocess with larger gaps.
 * Note that gap = 1 means normal insertion sort.
 * But due to preprocessing before gap = 1, we reduce the number of iterations of this normal insertion sort.
 * This is to take inversion pairs that are very far from each other.
 */
void shell_sort(int a[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
			for (int j = i; j >= gap; j -= gap)
				if (a[j] < a[j - gap])
					swap(&a[j], &a[j - gap]);
				else
					break;
}

void gen_shell_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
			for (int j = i; j >= gap; j -= gap)
				if (cmp(base + ((j - gap) * size), base + (j * size)))
					gen_swap(base + ((j - gap) * size), base + (j * size), size);
				else 
					break;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", gen_brute(gen_shell_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	gen_shell_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}
