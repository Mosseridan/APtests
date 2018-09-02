#include <stdio.h>
#include <stdlib.h>
#include <mat_mul.h>
#include <omp.h>

void mat_mul(int n, int* a, int* b, int* c) {
    int i;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        c[i] = b[i] * a[i];
    }
    return;
}

int compute_i(int i, int* a, int* b) {
    return a[i] * b[i];
}



void mat_mul_function_calls(int n, int* a, int* b, int* c) {
    int i;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        c[i] = compute_i(i, a, b);
    }
    return;
}


void mat_mul_loop_unroll3(int n, int* a, int* b, int* c) {
    int i;
    
    for (i = 0; i < n-1; i+=2) { // we asume that n is even
        c[i] = 0;
        c[i + 1] = 0;
        c[i] = b[i] * a[i];
        c[i + 1] = b[i + 1] * a[i + 1];
    }
    return;
}

void mat_mul_pointer_alias(int n, int* a, int* b, int* c) {
    int i;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        (*(c + i)) = (*(a+i)) * b[i];
    }
    return;
}


