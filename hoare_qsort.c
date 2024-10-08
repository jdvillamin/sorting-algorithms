#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	if (*a == *b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void init(int a[], int n) {
	int i;

	// ascending
	// for (i = 0; i < n; i++)
	// 	a[i] = i + 1;
	
	// descending
	// for (i = 0; i < n; i++)
	// 	a[i] = n - i;
	
	// random
	// initialize array a
	for (i = 0; i < n; i++)
	 	a[i] = i + 1;
	
	// set seed
	srand(7);
	// srand(13);
	// srand(17);
	
	for (i = 0; i < n; i++)
	 	swap(&a[i], &a[rand() % n]);
}

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
	int random_index = l + rand() % (h - l);
	swap(&a[l], &a[random_index]);
	int pivot = a[l], i = l, j = h - 1;
	while (1) {
		while (i < h && a[i] < pivot) i++;
		while (j > l && a[j] > pivot) j--;
		if (i >= j) break;
		swap(&a[i], &a[j]);
	}
	return j;
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

void output(int a[], int n) {
	int i;

	for (i = 0; i < n; i++)
		printf("%i\n", a[i]);
	printf("\n");
}

void check(int a[], int n) {
	int i, correct = 1;

	for (i = 0; i + 1 < n; i++) correct &= a[i] <= a[i + 1];
	printf("correct: %d\n", correct);
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int a[n];
	clock_t t1, t2;

	init(a, n);
	// output(a, n);

	t1 = clock();
	quick_sort(a, 0, n);
	t2 = clock();

	// output(a, n);
	check(a, n);
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / (double) CLOCKS_PER_SEC);
}

