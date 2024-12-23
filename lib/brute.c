#include <stdio.h>
#include <stdlib.h>
#include "brute.h"
#include "utils.h"

#define MAX_N 8

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
	if (p == -1) 
		return 0; // 0 means no more next permutation
	// find the maximum q such that a[p] < a[q] and swap them
	for (i = n - 1; i > p; i--) {
		if (a[i] > a[p]) {
			swap(&a[i], &a[p]);
			break;
		}
	}
	// reverse a[p + 1:n - 1]
	int start = p + 1, end = n - 1;
	while (start < end) {
		swap(&a[start], &a[end]);
		start++;
		end--;
	}
	return 1;
}

int brute(void (*sort)(int *, int)) {
	int a[MAX_N], p[MAX_N], n, i;
	for (n = 1; n <= MAX_N; n++) {
		for (i = 0; i < n; i++) 
			a[i] = i + 1;
		do {
			for (i = 0; i < n; i++) 
				p[i] = a[i];
			(*sort)(p, n);
			if (!check(p, n)) {
				fprintf(stderr, "error: wrong sort\n");
				fprintf(stderr, "permutation:\n");
				for (i = 0; i < n; i++) 
					fprintf(stderr, "%d ", p[i]);
				fprintf(stderr, "\n");
				return 0;
			}		
		} while (next_permutation(a, n));
	}
	return 1;
}

int gen_brute(void (*gen_sort)(void *, int, int, int (*cmp)(const void *, const void *))) {
	int a[MAX_N], p[MAX_N], n, i;
	for (n = 1; n <= MAX_N; n++) {
		for (i = 0; i < n; i++)
			a[i] = i + 1;
		do {
			for (i = 0; i < n; i++)
				p[i] = a[i];
			(*gen_sort)(p, n, sizeof(int), cmp_int);
			if (!check(p, n)) {
				fprintf(stderr, "error: wrong sort\n");
				fprintf(stderr, "permutation:\n");
				for (i = 0; i < n; i++) 
					fprintf(stderr, "%d ", p[i]);
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

