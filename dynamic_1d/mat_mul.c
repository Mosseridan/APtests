#include <mat_mul.h>

void mat_mul(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i*n+j] = 0;
            for (k = 0; k < n; k++) {
                c[i*n+j] += a[i*n+k] * b[k*n+j];
            }
        }
    }
    return;
}



int compute_cijk(int i, int j, int k, int n, int* a, int* b) {
    return a[i*n+k] * b[k*n+j];
}



void mat_mul_function_calls(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i*n+j] = 0;
            for (k = 0; k < n; k++) {
                c[i*n+j] += compute_cijk(i,j,k,n,a,b);
            }
        }
    }
    return;
}



void compute_cijk2(int i, int j, int k, int n, int* a, int* b, int* c) {
     c[i*n+j] += a[i*n+k] * b[k*n+j];
}



void mat_mul_function_calls2(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i*n+j] = 0;
            for (k = 0; k < n; k++) {
                compute_cijk2(i,j,k,n,a,b,c);
            }
        }
    }
    return;
}



void compute_cij(int i, int j , int n, int* a, int* b, int* c) {
    int k;
    c[i*n+j] = 0;
    for (k = 0; k < n; k++) {
        c[i*n+j] += a[i*n+k] * b[k*n+j];
    }
}



void mat_mul_function_calls3(int n, int* a, int* b, int* c) {  
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            compute_cij(i,j,n,a,b,c);
        }
    }
    return;
}



void compute_ci(int i, int n, int* a, int* b, int* c) {
    int j,k;
    for (j = 0; j < n; j++) {
        c[i*n+j] = 0;
        for (k = 0; k < n; k++) {
            c[i*n+j] += a[i*n+k] * b[k*n+j];
        }   
    } 
}



void mat_mul_function_calls4(int n, int* a, int* b, int* c) {  
    int i;
    for (i = 0; i < n; i++) {
        compute_ci(i,n,a,b,c);
    }
    return;
}



void mat_mul_loop_unroll(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i*n+j] = 0;
            for (k = 0; k < n-1; k += 2) { // we asume that n is even
                c[i*n+j] += (a[i*n+k] * b[k*n+j] + a[i*n+k+1] * b[(k+1)*n+j]);
            }
        }
    }
    return;
}



void mat_mul_loop_unroll2(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n-1; j+= 2) { // we asume that n is even
            c[i*n+j] = 0;
            c[i*n+j+1] = 0;
            for (k = 0; k < n-1; k += 2) { 
                c[i*n+j] += (a[i*n+k] * b[k*n+j] + a[i*n+k+1] * b[(k+1)*n+j]);
                c[i*n+j+1] += (a[i*n+k] * b[k*n+j+1] + a[i*n+k+1] * b[(k+1)*n+j+1]);
            }
        }
    }
    return;
}



void mat_mul_loop_unroll3(int n, int* a, int* b, int* c) {  
    int i,j,k;
    for (i = 0; i < n-1; i+=2) { // we asume that n is even
        for (j = 0; j < n-1; j+= 2) {
            c[i*n+j] = 0;
            c[i*n+j+1] = 0;
            c[(i+1)*n+j] = 0;
            c[(i+1)*n+j+1] = 0;
            for (k = 0; k < n-1; k += 2) { 
                c[i*n+j] += (a[i*n+k] * b[k*n+j] + a[i*n+k+1] * b[(k+1)*n+j]);
                c[i*n+j+1] += (a[i*n+k] * b[k*n+j+1] + a[i*n+k+1] * b[(k+1)*n+j+1]);
                c[(i+1)*n+j] += (a[(i+1)*n+k] * b[k*n+j] + a[(i+1)*n+k+1] * b[(k+1)*n+j]);
                c[(i+1)*n+j+1] += (a[(i+1)*n+k] * b[k*n+j+1] + a[(i+1)*n+k+1] * b[(k+1)*n+j+1]);
            }
        }
    }
    return;
}