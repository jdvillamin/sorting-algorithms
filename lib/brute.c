#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int next_permutation(int a[], int n) {
	int i, p, q;
	// find the maximum p such that a[p] < a[p + 1]
	// if p doesn't exist, then this is the last permutation
	p = -1; // -1 means it doesn't exist
	for (i = n - 2; i >= 0; i--) {
		if (a[i] < a[i + 1]) {
			p = i;
			break;
		}
	}
	if (p == -1) return 0; // 0 means no more next permutation
	// find the maximum q such that p < q and a[p] < a[q]
	q = p + 1; // q should always exist
	for (i = n - 1; i > p + 1; i--) {
		if (a[p] < a[i]) {
			q = i;
			break;
		}
	}
	swap(&a[p], &a[q]);
	// reverse a[p + 1:q]
	for (i = p + 1; i < p + 1 + (q - p) / 2; i++) {
		swap(&a[i], &a[q - (i - p - 1)]);
	}
	return 1;
}

int brute(void (*sort)(int *, int), int max_n) {
	int a[max_n], p[max_n], n, i;
	for (n = 1; n <= max_n; n++) {
		for (i = 0; i < n; i++) {
			a[i] = i + 1;
		}
		do {
			for (i = 0; i < n; i++) {
				p[i] = a[i];
			}
			(*sort)(p, n);
			if (!check(p, n)) {
				fprintf(stderr, "error: wrong sort\n");
				fprintf(stderr, "permutation:\n");
				for (i = 0; i < n; i++) fprintf(stderr, "%d ", p[i]);
				fprintf(stderr, "\n");
				return 0;
			}		
		} while (next_permutation(a, n));
	}
	return 1;
}

/*
 * 1 4 5 8 9 2 3 7 6
 *
 * 1 4 5 8 9 2 6 3 7
 *
 * 1 4 5 8 9 2 6 7 3
 *
 * 1 4 5 8 9 2 7 6 3
 *           p     q
 * 2 < 7 => p = 2
 * 3 is the lowest higher number than p say q
 * but after p, every integer is decreasing
 *
 * swap p and q
 *
 * 1 4 5 8 9 3 7 6 2
 *           p     q
 * reverse from the right of p up to q       
 * 1 4 5 8 9 3 2 6 7
 */

