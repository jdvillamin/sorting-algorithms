#include <stdio.h>
#include <stdlib.h>
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

/*
 * Use insertion sort, but preprocess with larger gaps.
 * Note that gap = 1 means normal insertion sort.
 * But due to preprocessing before gap = 1, we reduce the number of iterations of this normal insertion sort.
 * This is to take inversion pairs that are very far from each other.
 */
void shsort(int a[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
			for (int j = i; j >= gap; j -= gap)
				if (a[j] < a[j - gap])
					swap(&a[j], &a[j - gap]);
				else
					break;
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

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int a[n];
	clock_t t1, t2;

	init(a, n);
	// output(a, n);

	t1 = clock();
	shsort(a, n);
	t2 = clock();

	// output(a, n);
	check(a, n);
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / (double) CLOCKS_PER_SEC);
}

