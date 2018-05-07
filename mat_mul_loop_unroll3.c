#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char** argv) {

    char *p;
    int n = 10000;
    errno = 0;
  
    if (argc >= 2) {
        long conv = strtol(argv[1], &p, 10);
        // Check for errors: e.g., the string does not represent an integer
        // or the integer is larger than int
         if (errno == 0 && *p == '\0' && conv <= INT_MAX) {
            n = conv;
         }
    }

    printf("n is set to %d\n",n);

    clock_t begin = clock();

    int i,j,k;    
    int** a = malloc (sizeof(int)*n);  
    int** b = malloc (sizeof(int)*n);  
    int** c = malloc (sizeof(int)*n);  
    
    printf("initializeing a and b with pseudo random numbers and c with zeros\n");
    clock_t init_begin = clock();
    
    srand(time(NULL)); // generate rand seed from current time    

    // initialize a and b with pseudo random numbers and c with zeros
    for (i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int)*n);
        b[i] = malloc(sizeof(int)*n);
        c[i] = malloc(sizeof(int)*n);
        for (j = 0; j < n; j++) {
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
    for (i = 0; i < n-1; i+=2) { // we asume that n is even
        for (j = 0; j < n-1; j+= 2) { 
            for (k = 0; k < n-1; k += 2) { 
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]);
                c[i][j+1] += (a[i][k] * b[k][j+1] + a[i][k+1] * b[k+1][j+1]);
                c[i+1][j] += (a[i+1][k] * b[k][j] + a[i+1][k+1] * b[k+1][j]);
                c[i+1][j+1] += (a[i+1][k] * b[k][j+1] + a[i+1][k+1] * b[k+1][j+1]);
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