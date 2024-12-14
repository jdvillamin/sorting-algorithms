#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

/*
 * Use insertion sort, but preprocess with larger gaps.
 * Note that gap = 1 means normal insertion sort.
 * But due to preprocessing before gap = 1, we reduce the number of iterations of this normal insertion sort.
 * This is to take inversion pairs that are very far from each other.
 */
void shell_sort(int a[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
			for (int j = i; j >= gap; j -= gap)
				if (a[j] < a[j - gap])
					swap(&a[j], &a[j - gap]);
				else
					break;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: <array size> <asc|desc|rand> [<seed>]\n");
		exit(1);
	}
	
	if (!brute(shell_sort)) {
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
	shell_sort(a, n);
	t2 = clock();

	if (!check(a, n)) {
        fprintf(stderr, "Failed main input case check\n");
        exit(1);
    }
    
	printf("%0.6f ", (double) (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}
