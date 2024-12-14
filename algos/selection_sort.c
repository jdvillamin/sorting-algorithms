#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void selection_sort(int a[], int n) {
	int i, j, min_idx;
	for (i = 0; i < n; i++) {
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min_idx])
				min_idx = j;
		swap(&a[i], &a[min_idx]);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}
	
	if (!brute(selection_sort)) {
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
	selection_sort(a, n);
	t2 = clock();

	if (!check(a, n)) {
        fprintf(stderr, "Failed main input case check\n");
        exit(1);
    }
    
	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
