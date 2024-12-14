#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void gen_merge(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
    int i, j, k, mid = n / 2;

    void *temp = malloc(n * size);

    for (i = 0, j = mid, k = 0; k < n; k++)
        memcpy(
            temp + k * size, 
            (j == n || i < mid && cmp(base + j * size, base + i * size)) ? 
                base + i++ * size : 
                base + j++ * size,
            size
        );
    
    memcpy(base, temp, n * size);
    free(temp);
}

void gen_merge_sort(void *base, int n, int size, int (*cmp)(const void *, const void *)) {
    if (n > 1) {
        gen_merge_sort(base, n / 2, size, cmp);
        gen_merge_sort(base + (n / 2) * size, n - n / 2, size, cmp);
        gen_merge(base, n, size, cmp);
    }
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}

	if (!gen_brute(gen_merge_sort)) {
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
	gen_merge_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	if (!check(a, n)) {
		fprintf(stderr, "Failed main input case check\n");
		exit(1);
	}

	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
