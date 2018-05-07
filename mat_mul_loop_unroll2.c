#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

int main(int argc, char** argv) {

    clock_t begin = clock();

    int i,j,k;    
    int** a = malloc (sizeof(int)*N);  
    int** b = malloc (sizeof(int)*N);  
    int** c = malloc (sizeof(int)*N);  
    
    printf("initializeing a and b with pseudo random numbers and c with zeros\n");
    clock_t init_begin = clock();
    
    srand(time(NULL)); // generate rand seed from current time    

    // initialize a and b with pseudo random numbers and c with zeros
    for (i = 0; i < N; i++) {
        a[i] = malloc(sizeof(int)*N);
        b[i] = malloc(sizeof(int)*N);
        c[i] = malloc(sizeof(int)*N);
        for (j = 0; j < N; j++) {
            a[i][j] = rand();
            b[i][j] = rand();
            c[i][j] = 0;
        }
    }

    clock_t init_end = clock();
    double init_time_spent = (double)(init_end - init_begin) / CLOCKS_PER_SEC;
    printf("initialization took %f seconds\n",init_time_spent);

    printf("computing c = a*b\n");
    clock_t calc_begin = clock();

    // compute c = a*b
    for (i = 0; i < N; i++) {
        for (j = 0; j < N-1; j+= 2) { // we asume that N is even
            for (k = 0; k < N-1; k += 2) { 
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]);
                c[i][j+1] += (a[i][k] * b[k][j+1] + a[i][k+1] * b[k+1][j+1]);
            }
        }
    }


    clock_t calc_end = clock();
    double calc_time_spent = (double)(calc_end - calc_begin) / CLOCKS_PER_SEC;
    printf("calculation took %f seconds\n",calc_time_spent);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("program execution took %f seconds\n",time_spent);
    
    return 0;

}