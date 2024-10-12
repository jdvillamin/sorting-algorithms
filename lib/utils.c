#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int min(int a, int b) {
	return a < b ? a : b;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void init(int a[], int n, const char *mode, int seed) {
	int i;
	
	if (strcmp(mode, "asc") == 0) {
		for (i = 0; i < n; i++)
			a[i] = i + 1;
	} else if (strcmp(mode, "desc") == 0) {
		for (i = 0; i < n; i++)
	    		a[i] = n - i;
	} else if (strcmp(mode, "rand") == 0) {
		for (i = 0; i < n; i++)
	    		a[i] = i + 1;

		srand(seed);

		for (i = 0; i < n; i++)
	    		swap(&a[i], &a[rand() % n]);
	} else {
		printf("unknown mode: %s\n", mode);
		exit(1);
	}
}

void output(int a[], int n) {
	for (int i = 0; i < n; i++)
        	printf("%i\n", a[i]);
    	printf("\n");
}

int check(int a[], int n) {
	int correct = 1;

	for (int i = 0; i + 1 < n; i++)
        	correct &= a[i] <= a[i + 1];
	return correct;
}

