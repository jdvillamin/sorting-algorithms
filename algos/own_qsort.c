#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

/*
 * Partition algorithm:
 * Note that all elements that is less than a[p] must be to its left.
 * Thus, these elements must form a prefix of a[l:h].
 * The idea is to build this prefix.
 * Suppose we pick the last element as the pivot.
 * To avoid corner cases, we swap it with a random element in the subrange.
 * To build the prefix, maintain two pointers i, j.
 * i keeps track of the last element in the prefix.
 * j moves to swap elements less than pivot to the last element of the prefix.
 */
int partition(int a[], int l, int h) {
	swap(&a[h - 1], &a[l + rand() % (h - l)]);
	int pivot = a[h - 1], i = l, j;
	for (j = l; j < h - 1; j++) {
		if (a[j] < pivot) {
			swap(&a[i], &a[j]);
			i++;
		}
	}
	swap(&a[h - 1], &a[i]);
	return i;
}

/*
 * Quick sort:
 * Suppose we want to sort the array from l to h (exclusive).
 * We want to pick a partition element a[p] (l <= p < h).
 * We want to find where a[p] is supposed to be in the subrange.
 * We can do this by placing all elements less then a[p] to the left of a[p],
 * and all elements greater than or equal to a[p] to the right of a[p].
 * After that, recurse to the subranges (l, p) and (p + 1, h).
 * If we keep the partitioning algorithm to be O(h - l),
 * then by Master's theorem, our algorithm will be O(n log n)
 * if we get lucky with the partitioning element that it halves the subranges.
 */
void quick_sort(int a[], int l, int h) {
	if (h - l < 2) return;
	int p = partition(a, l, h);
	quick_sort(a, l, p);
	quick_sort(a, p + 1, h);
}

void own_qsort(int a[], int n) {
	quick_sort(a, 0, n);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", brute(own_qsort, 10));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	own_qsort(a, n);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

