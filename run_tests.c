#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <mat_mul.h>

#define N_TESTS 8
#define EPS 0

typedef void (*test_type)(int n,int* a ,int* b,int* c);

void free_mat(int n, int** mat) {
    int i;
    for(i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}


int main(int argc, char** argv) {

    char *p;
    int n = 1000;
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
    int mat_size_bm =  n*n*sizeof(int);
    printf("each matrix takes %d Bytes\ntotal usage of matrices a,b,c and d is %d Bytes\n",mat_size_bm,4*mat_size_bm);
    // array of tests to be executed
    
    test_type tests[N_TESTS] = { 
        &mat_mul,
        &mat_mul_function_calls,
        &mat_mul_function_calls2,
        &mat_mul_function_calls3,
        &mat_mul_function_calls4,
        &mat_mul_loop_unroll,
        &mat_mul_loop_unroll2,
        &mat_mul_loop_unroll3
    };

    const char* test_names[N_TESTS] = { 
        "mat_mul",
        "mat_mul_function_calls",
        "mat_mul_function_calls2",
        "mat_mul_function_calls3",
        "mat_mul_function_calls4",
        "mat_mul_loop_unroll",
        "mat_mul_loop_unroll2",
        "mat_mul_loop_unroll3",
    };

    clock_t begin, end;
    double time_spent;
    int i,j,k;    
    int* a = malloc (sizeof(int)*n*n);  
    int* b = malloc (sizeof(int)*n*n);  
    int* c = malloc (sizeof(int)*n*n);  
    int* d = malloc (sizeof(int)*n*n);
    printf("initializeing a and b with pseudo random numbers and c with zeros\n");
    begin = clock();
    
    srand(time(NULL)); // generate rand seed from current time    

    // initialize a and b with pseudo random numbers between 0 to 99
    for (i = 0; i < n*n; i++) {
        a[i] = rand() % 2;
        b[i] = rand() % 2;
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("initialization took %f seconds\n", time_spent);
  
    printf("computing d = a*b with a serial calculating\n");
    begin = clock();
    tests[0](n, a, b, d);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("finished computing d, in %f seconds\n", time_spent);
    // run all tests with a,b,c and n
    for(k = 0; k < N_TESTS; k++) {
        printf("\ncomputing c = a*b with test: %s\n",test_names[k]);
        begin = clock();
        tests[k](n, a, b, c);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("finished test: %s, in %f seconds\n", test_names[k], time_spent);
        printf("verifying that c == d\n");
        int bad = 0;
        for(i = 0; i < n*n; i++) {
            int err = abs(c[i] - d[i]);
            if(err > EPS) {
                printf("BAD RSULTS in test: %s! err: %d i: %d j: %d\n",test_names[k],err,i,j);
                printf("c[%d]: %d\n",i,c[i]);
                printf("d[%d]: %d\n",i,d[i]);
                break;
            }
        }
    }
        
    free(a);
    free(b);
    free(c);
    free(d);
    
    return 0;

}
    