#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void init(int a[], int n) {
	int i;

	// ascending
	// for (i = 0; i < n; i++)
	//	a[i] = i + 1;

	// descending
	// for (i = 0; i < n; i++)
	 	// a[i] = n - i;

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

void isort(int a[], int n) {
	int i, j;

	for (i = 1; i < n; i++)
		for (j = i; j > 0; j--)
			if (a[j - 1] > a[j])
				swap(&a[j - 1], &a[j]);
			else break;
}

void output(int a[], int n) {
	int i;

	for (i = 0; i < n; i++)
		printf("%i\n", a[i]);
	printf("\n");
}

int main() {
	// int n = 10; // should be set depending on the machine
	int n = 46000;
	int a[n], i;
	clock_t t1, t2;

	init(a, n);
	// output(a, n); // comment output calls for very large values of n

	t1 = clock();
	// sorting algorithm
	isort(a, n);
	t2 = clock();

	// output(a, n);
	printf("time elapsed: %0.6f\n", (double) (t2 - t1) / (double) CLOCKS_PER_SEC);
}

