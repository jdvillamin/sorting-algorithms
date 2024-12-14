#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void gen_percolate_down(void *base, int n, int i, int size, int (*cmp)(const void *, const void *)) {
    int left, right;
    while (2 * i + 1 < n) {
        left = 2 * i + 1, right = 2 * i + 2;
        if (cmp(base + left * size, base + i * size) && (right >= n || cmp(base + left * size, base + right * size))) {
            gen_swap(base + i * size, base + left * size, size);
            i = left;
        } else if (right < n && cmp(base + right * size, base + i * size)) {
            gen_swap(base + i * size, base + right * size, size);
            i = right;
        } else
            break;
    }
}

void gen_heap_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i--)
        gen_percolate_down(base, n, i, size, cmp);

    int last = n;
    for (i = 0; i < n - 1; i++) {
        gen_swap(base + 0 * size, base + --last * size, size);
        gen_percolate_down(base, last, 0, size, cmp);
    }
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}

	if (!gen_brute(gen_heap_sort)) {
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
	gen_heap_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	if (!check(a, n)) {
		fprintf(stderr, "Failed main input case check\n");
		exit(1);
	}

	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
