#ifndef UTILS_H
#define UTILS_H

void swap(int *a, int *b);
void init(int a[], int n, const char *mode, int seed);
void output(int a[], int n);
int check(int a[], int n);
int cmp_int(const void *p1, const void *p2);
void gen_swap(const void *p1, const void *p2, int size);

#endif
