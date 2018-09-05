#include <mat_mul.h>
#include <size.h>

void mat_mul(int* a, int* b, int* c) {  
    int i,j,k,t;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {         
            c[i*N+j] = 0;    
            for (k = 0; k < N; k++) {
                for (t = 0; t < 100; t++) {
                    c[i*N+j] += a[i*N+k] * b[j*N+k];
                }
            }
        }
    }
    return;
}
