#include <stdio.h>
#include <stdlib.h>
#include <mat_mul_dyn.h>

void mat_mul(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return;
}



int compute_cijk(int i, int j, int k, int** a, int** b) {
    return a[i][k] * b[k][j];
}



void mat_mul_function_calls(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n; k++) {
                c[i][j] += compute_cijk(i,j,k,a,b);
            }
        }
    }
    return;
}



void compute_cijk2(int i, int j, int k, int** a, int** b, int** c) {
     c[i][j] += a[i][k] * b[k][j];
}



void mat_mul_function_calls2(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n; k++) {
                compute_cijk2(i,j,k,a,b,c);
            }
        }
    }
    return;
}



void compute_cij(int i, int j , int n, int** a, int** b, int** c) {
    int k;
    c[i][j] = 0;
    for (k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
    }
}



void mat_mul_function_calls3(int n, int** a, int** b, int** c) {  
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            compute_cij(i,j,n,a,b,c);
        }
    }
    return;
}



void compute_ci(int i, int n, int** a, int** b, int** c) {
    int j,k;
    for (j = 0; j < n; j++) {
        c[i][j] = 0;
        for (k = 0; k < n; k++) {
            c[i][j] += a[i][k] * b[k][j];
        }   
    } 
}



void mat_mul_function_calls4(int n, int** a, int** b, int** c) {  
    int i;
    for (i = 0; i < n; i++) {
        compute_ci(i,n,a,b,c);
    }
    return;
}



void mat_mul_loop_unroll(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n-1; k += 2) { // we asume that n is even
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]);
            }
        }
    }
    return;
}



void mat_mul_loop_unroll2(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n-1; j+= 2) { // we asume that n is even
            c[i][j] = 0;
            c[i][j+1] = 0;
            for (k = 0; k < n-1; k += 2) { 
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]);
                c[i][j+1] += (a[i][k] * b[k][j+1] + a[i][k+1] * b[k+1][j+1]);
            }
        }
    }
    return;
}



void mat_mul_loop_unroll3(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n-1; i+=2) { // we asume that n is even
        for (j = 0; j < n-1; j+= 2) {
            c[i][j] = 0;
            c[i][j+1] = 0;
            c[i+1][j] = 0;
            c[i+1][j+1] = 0;
            for (k = 0; k < n-1; k += 2) { 
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]);
                c[i][j+1] += (a[i][k] * b[k][j+1] + a[i][k+1] * b[k+1][j+1]);
                c[i+1][j] += (a[i+1][k] * b[k][j] + a[i+1][k+1] * b[k+1][j]);
                c[i+1][j+1] += (a[i+1][k] * b[k][j+1] + a[i+1][k+1] * b[k+1][j+1]);
            }
        }
    }
    return;
}


void mat_mul_arr_priv(int n, int** a, int** b, int** c) {  
    int i,j,k;
    int* d = malloc(sizeof(int)*n);
    for (i = 0; i < n; i++) {
        d[i] = 0;
        for (j = 0; j < n; j++) {
            d[i] = i;
            c[d[i]][j] = 0;
            for (k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return;
}


void mat_mul_arr_priv2(int n, int** a, int** b, int** c) {  
    int i,j,k;
    int* d = malloc(sizeof(int)*n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            d[i] = 0;
            for (k = 0; k < n; k++) {
                d[i] += a[i][k] * b[k][j];
            }
            c[i][j] = d[i];
        }
    }
    return;
}


void mat_mul_pointer_alias(int n, int** a, int** b, int** c) {  
    int i,j,k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n; k++) {
                (*(c+i))[j] += (*(a+i))[k] * b[k][j];
            }
        }
    }
    return;
}


void mat_mul_pointer_alias2(int n, int** a, int** b, int** c) {  
    int i,j,k;
    int** d = c;
    for (i = 0; i < n; i++) { 
        c[i][0] = 0;
        for (j = 1; j < n; j++) {
            c[i][j] = d[i][j-1];
        }
    }
    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return;
}
