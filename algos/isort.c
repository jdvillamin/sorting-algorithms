#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

/*
 * [                        ]
 * 
 * [sorted][    unsorted    ]
 *
 * We insert elements from the unsorted part to the sorted part.
 *
 * We build the sorted part expanding from left to right.
 *
 * [  sorted  ][  unsorted  ]
 *
 * [         sorted         ]
 *
 * 3 1 4 2 5 6 0 8 7
 *
 * [3] 1 4 2 5 6 0 8 7
 *
 * We can pick the first element in the unsorted part.
 *
 * Swap it with the element to its left until we get swap it to the correct position.
 *
 * This takes advantage of the fact that the sorted part is sorted.
 *
 * [1] 3 4 2 5 6 0 8 7
 *
 * [1 3] 4 2 5 6 0 8 7
 *
 * [1 3 4] 2 5 6 0 8 7
 *
 * [1 3 2] 4 5 6 0 8 7
 *
 * [1 2 3 4] 5 6 0 8 7
 *
 * [1 2 3 4 5 6] 0 8 7
 *
 * [1 2 3 4 5 0] 6 8 7
 *
 * [1 2 3 4 0 5] 6 8 7
 *
 * [1 2 3 0 4 5] 6 8 7
 *
 * ...
 * 
 * [0 1 2 3 4 5 6] 8 7
 *
 * [0 1 2 3 4 5 6 8] 7
 *
 * [0 1 2 3 4 5 6 7 8]
 * 
 * The insertion point must be the right most position such that the previos element is less than or equal to the inserted element.
 */
void isort(int a[], int n) {
	int i, j;

	for (i = 1; i < n; i++)
		for (j = i; j > 0; j--)
			if (a[j - 1] > a[j])
				swap(&a[j - 1], &a[j]);
			else break;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("wrong usage\n");
		return 1;
	}
	
	printf("brute result: %d\n", brute(isort, 10));
	
	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc == 4) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	isort(a, n);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}

