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

int gen_partition(void *base, int l, int h, int size, int (*cmp)(const void *, const void *)) {
    gen_swap(base + h * size, base + (l + rand() % (h - l + 1)) * size, size);
    void *pivot = base + h * size;
    int i = l, j;
    for (j = l; j < h; j++) {
        if (cmp(pivot, base + j * size)) {
            gen_swap(base + i++ * size, base + j * size, size);
        }
    }
    gen_swap(base + h * size, base + i * size, size);
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
void gen_own_quick_sort_helper(void *base, int l, int h, int size, int (*cmp)(const void *, const void *)) {
    if (l >= h) return;
    int p = gen_partition(base, l, h, size, cmp);
    gen_own_quick_sort_helper(base, l, p - 1, size, cmp);
    gen_own_quick_sort_helper(base, p + 1, h, size, cmp);
}

void gen_own_quick_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
    gen_own_quick_sort_helper(base, 0, n - 1, size, cmp);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}

	if (!gen_brute(gen_own_quick_sort)) {
		fprintf(stderr, "Failed brute force verification\n");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc == 4) ? atoi(argv[3]) : 0;

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	gen_own_quick_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	if (!check(a, n)) {
		fprintf(stderr, "Failed main input case check\n");
		exit(1);
	}

	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
