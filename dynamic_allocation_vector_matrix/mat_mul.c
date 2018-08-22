#include <stdio.h>
#include <stdlib.h>
#include <mat_mul.h>
#include <omp.h>

void mat_mul(int n, int* a, int** b, int* c) {
    int i,j,k;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        for (j = 0; j < n; j++) {
            c[i] += b[i][j] * a[j];
        }
    }
    return;
}

int compute_cijk(int i, int j, int* a, int** b) {
    return a[j] * b[i][j];
}



void mat_mul_function_calls(int n, int* a, int** b, int* c) {
    int i,j;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        for (j = 0; j < n; j++) {
            c[i] += compute_cijk(i,j,a,b);
        }
    }
    return;
}


void mat_mul_loop_unroll3(int n, int* a, int** b, int* c) {
    int i,j,k;
    for (i = 0; i < n-1; i+=2) { // we asume that n is even
        c[i] = 0;
        c[i + 1] = 0;
        for (j = 0; j < n-1; j+= 2) {
            c[i] += b[i][j] * a[j];
            c[i] += b[i][j + 1] * a[j + 1];
            c[i + 1] += b[i + 1][j] * a[j];
            c[i + 1] += b[i + 1][j+1] * a[j + 1];
        }
    }
    return;
}

void mat_mul_pointer_alias(int n, int* a, int** b, int* c) {
    int i,j,k;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        for (j = 0; j < n; j++) {
            (*(c+i)) += (*(a+j)) * b[i][j];
        }
    }
    return;
}


