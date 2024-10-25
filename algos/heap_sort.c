#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void percolate_down(int a[], int n, int i) {
	// while left child exists, percolate down while it is possible
	int left, right;
	while (2 * i + 1 < n) {
		left = 2 * i + 1, right = 2 * i + 2;
		if (a[i] < a[left] && (right >= n || a[left] > a[right])) {
			swap(&a[i], &a[left]);
			i = left;
		} else if (right < n && a[i] < a[right]) {
			swap(&a[i], &a[right]);
			i = right;
		} else
			break;
	}
}

void heap_sort(int a[], int n) {
	// i is mapped to 2i + 1 and 2i + 2
	// so, parent(i) = (i - 1) / 2
	int i;
	for (i = (n - 2) / 2; i >= 0; i--)
		percolate_down(a, n, i);
	
	// keep deleting maximum
	int last = n;
	for (i = 0; i < n - 1; i++) {
		// max is at a[0]
		swap(&a[0], &a[--last]);
		percolate_down(a, last, 0);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}

	printf("brute result: %d\n", brute(heap_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	heap_sort(a, n);
	t2 = clock();
	
	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);
	
	return 0;
}

