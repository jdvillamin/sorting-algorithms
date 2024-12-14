#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

/*
 * Hoare partition scheme: https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
 * Use two pointers: i and j.
 * Initially i is set to l and j is set to h.
 * We move i towards right and j towards left.
 * We want to build a prefix of elements less than the pivot.
 * We want to build a suffix of elements greater than the pivot.
 * If we find a[i] > p, we stop i at the moment.
 * If we find a[j] < p, we stop j at the moment.
 * We swap a[i] and a[j] if i and j are still in the correct order.
 * Otherwise, we know that j is the partition position.
 */
int partition(int a[], int l, int h) {
	swap(&a[l], &a[l + rand() % (h - l + 1)]);
	int pivot = a[l], i = l, j = h;
	while (1) {
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
		if (i >= j) 
			break;
		swap(&a[i], &a[j]);
	}
	return j;
}

void insertion_sort(int a[], int n) {
	int i, j;

	for (i = 1; i < n; i++)
		for (j = i; j > 0; j--)
			if (a[j - 1] > a[j])
				swap(&a[j - 1], &a[j]);
			else 
				break;
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
void hoare_quick_sort_helper(int a[], int l, int h) {
	if (l >= h) return;
    if (h - l <= 15)
        insertion_sort(a + l, h - l + 1);
	int p = partition(a, l, h);
	hoare_quick_sort_helper(a, l, p - 1);
	hoare_quick_sort_helper(a, p + 1, h);
}

void hoare_quick_sort(int a[], int n) {
	hoare_quick_sort_helper(a, 0, n - 1);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", brute(hoare_quick_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	hoare_quick_sort(a, n);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}
