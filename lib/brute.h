#ifndef BRUTE_H
#define BRUTE_H

int next_permutation(int a[], int n);
int brute(void (*)(int *, int));
int gen_brute(void (*gen_sort)(void *, int, int, int (*cmp)(const void *p1, const void *p2)));

#endif
