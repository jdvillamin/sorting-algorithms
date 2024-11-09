#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/brute.h"

void merge(int a[], int n) {
	int i, j, k, mid = n / 2, temp[n];

	for (i = 0, j = mid, k = 0; k < n; k++)
		temp[k] = (j == n || i < mid && a[i] < a[j]) ? a[i++] : a[j++];
	
	memcpy(a, temp, n * sizeof(int));
}

void merge_sort(int a[], int n) {
	if (n > 1) {
		merge_sort(a, n / 2);
		merge_sort(&a[n / 2], n - n / 2);
		merge(a, n);
	}
}

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
		printf("wrong usage\n");
		return 1;
	}
	
	printf("brute result: %d\n", gen_brute(gen_merge_sort));

	int n = atoi(argv[1]);
	const char *mode = argv[2];
	int seed = (argc > 3) ? atoi(argv[3]) : time(NULL);

	int a[n];
	clock_t t1, t2;

	init(a, n, mode, seed);

	t1 = clock();
	gen_merge_sort(a, n, sizeof(int), cmp_int);
	t2 = clock();

	printf("correct: %d\n", check(a, n));
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	return 0;
}
