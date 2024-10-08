#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b) {
	if (*a == *b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void init(int a[], int n) {
        int i;

        // ascending
	// for (i = 0; i < n; i++)
        //	a[i] = i + 1;

        // descending
        // for (i = 0; i < n; i++)
        //	a[i] = n - i;

        // random
        // initialize array a
        for (i = 0; i < n; i++)
        	a[i] = i + 1;

        // set seed
        srand(7);
        // srand(13);
        // srand(17);
        
        for (i = 0; i < n; i++)
         	swap(&a[i], &a[rand() % n]);
}

void merge(int a[], int n) {
	int i, j, k, mid = n / 2, temp[n];

	for (i = 0, j = mid, k = 0; k < n; k++)
		temp[k] = (j >= n || i < mid && a[i] < a[j]) ? a[i++] : a[j++];
	
	memcpy(a, temp, n * sizeof(int));
}

void msort(int a[], int n) {
	if (n > 1) {
		msort(a, n / 2);
		msort(&a[n / 2], n - n / 2);
		merge(a, n);
	}
}

void output(int a[], int n) {
        int i;

        for (i = 0; i < n; i++)
                printf("%i\n", a[i]);
        printf("\n");
}

void check(int a[], int n) {
	int i, correct = 1;

	for (i = 0; i + 1 < n; i++) correct &= a[i] <= a[i + 1];
	printf("correct: %d\n", correct);
}

int main() {
        int n = 40000;
        int a[n], i;
        clock_t t1, t2;

        init(a, n);
        // output(a, n);

        t1 = clock();
        msort(a, n);
        t2 = clock();

        // output(a, n);
	check(a, n);
        printf("time elapsed: %0.6f\n", (double) (t2 - t1) / (double) CLOCKS_PER_SEC);
}

