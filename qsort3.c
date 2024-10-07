#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Let a0, b0 be the initial values of a and b.
 * a1 = a0 XOR b0
 * b1 = a1 XOR b0 = a0 XOR b0 XOR b0 = a0
 * a2 = a1 XOR b1 = a0 XOR b0 XOR a0 = b0
 */
void swap(int *a, int *b) {
	if (*a == *b) return;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void init(int a[], int n) {
	int i;

	// ascending
	// for (i = 0; i < n; i++)
	// 	a[i] = i + 1;
	
	// descending
	// for (i = 0; i < n; i++)
	// 	a[i] = n - i;
	
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

void output(int a[], int n) {
	int i;

	for (i = 0; i < n; i++)
		printf("%i\n", a[i]);
	printf("\n");
}

/*
 * Function to check if the resulting array is correctly sorted.
 */
void check(int a[], int n) {
	int i, correct = 1;

	for (i = 0; i + 1 < n; i++) correct &= a[i] <= a[i + 1];
	printf("correct: %d\n", correct);
}

int compare(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int main() {
	// int n = 5;
	int n = 100000;
	int a[n], i;
	clock_t t1, t2;

	init(a, n);
	// output(a, n);

	t1 = clock();
	qsort(a, n, sizeof(int), compare);
	t2 = clock();

	// output(a, n);
	check(a, n);
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / (double) CLOCKS_PER_SEC);
}

