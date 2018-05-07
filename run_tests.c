#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <mat_mul.h>

#define N_TESTS 8
#define EPS 0

typedef void (*test_type)(int n,int** a ,int** b,int** c);

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
    int** a = malloc (sizeof(int)*n);  
    int** b = malloc (sizeof(int)*n);  
    int** c = malloc (sizeof(int)*n);  
    int** d = malloc (sizeof(int)*n);
    printf("initializeing a and b with pseudo random numbers and c with zeros\n");
    begin = clock();
    
    srand(time(NULL)); // generate rand seed from current time    

    // initialize a and b with pseudo random numbers between 0 to 99
    for (i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int)*n);
        b[i] = malloc(sizeof(int)*n);
        c[i] = malloc(sizeof(int)*n);
        d[i] = malloc(sizeof(int)*n);
        for (j = 0; j < n; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("initialization took %f seconds\n", time_spent);
  
    printf("@@@ %d : %d\n",a[0][0], b[0][0]);
    printf("computing d = a*b with a serial calculating\n");
    begin = clock();
    tests[0](n, a, b, d);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("finished computing d, in %f seconds\n", time_spent);
    printf("@@@ %d : %d\n",a[0][0], b[0][0]);
    // run all tests with a,b,c and n
    for(k = 0; k < N_TESTS-1; k++) {
        printf("\ncomputing c = a*b with test: %s\n",test_names[k]);
        begin = clock();
        tests[k](n, a, b, c);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("finished test: %s, in %f seconds\n", test_names[k], time_spent);
        printf("verifying that c == d\n");
        int bad = 0;
        for(i = 0; i < n && !bad; i++) {
            for(j = 0; j < n && !bad; j++) {
                int err = abs(c[i][j] - d[i][j]);
                if(err > EPS){
                    printf("@@@ %d : %d\n",a[0][0], b[0][0]);
                    printf("BAD RSULTS in test: %s! err: %d i: %d j: %d\n",test_names[k],err,i,j);
                    printf("c[%d][%d]: %d, d[%d][%d]: %d\n",i,j,c[i][j],i,j,d[i][j]);
                    printf("%X %X %X %X\n",c,c[i],d,d[i]);
                    bad = 1;
                }
            }
        }
    }
        
    // free_mat(n, a);
    // free_mat(n, b);
    // free_mat(n, c);
    
    return 0;

}
    