#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <utils.h>
#include <mat_mul.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define N_TESTS 12

typedef void (*test_type)(int n,int** a ,int** b,int** c);

void mat_mul_serial(int n, int** a, int** b, int** c) {
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


void run_test(test_type test, const char* test_name, int n, int** a, int** b, int** c, int** d) {
    int i,j;
    double start, end;
    printf("\ncomputing c = a*b with test: %s\n",test_name);        
    // fprintf(fp, "\ncomputing c = a*b with test: %s\n",test_names[k]);
    start = omp_get_wtime();
    test(n, a, b, c);
    end = omp_get_wtime();
    printf("finished test: %s, in %lf seconds\n", test_name, end - start);
    // fprintf(fp, "finished test: %s, in %lf seconds\n", test_names[k], end - start);
    printf("verifying that c == d\n");        
    // fprintf(fp, "verifying that c == d\n");
    if (compare_pat(n, &i, &j, c, d)) {
        printf("BAD RSULTS in test: %s!, c[%d][%d]: %d, d[%d][%d]: %d\n",test_name,i,j,c[i][j],i,j,d[i][j]);  
    }
}


int main(int argc, char** argv) {

    char *p;
    long n = 1000;
    long test_num = -1;
    errno = 0;
    
    // FILE* fp;
    // char filename[40];
    // struct tm *timenow;

    // time_t now = time(NULL);
    // timenow = gmtime(&now);

    // strftime(filename, sizeof(filename), "test_log_%Y%m%d%H%M%S.log", timenow);
    // printf("using %s to log test results\n",filename);

    // fp = fopen(filename,"w");

  
    if (argc >= 2) {
        long conv = strtol(argv[1], &p, 10);
        // Check for errors: e.g., the string does not represent an integer
        // or the integer is larger than int
         if (errno == 0 && *p == '\0' && conv <= INT_MAX) {
            n = conv;
         }
         
         if (argc >= 3) {
            conv = strtol(argv[2], &p, 10);
            test_num = conv;
         }
    }

    printf("n is set to %d\n",n);    
    // fprintf(fp,"n is set to %d\n",n);
    double mat_size_bm = (double)n*(double)n*sizeof(int)+(double)n*sizeof(int*);
    printf("each matrix takes %g Bytes\ntotal usage of matrices a,b,c and d is %g Bytes\n",mat_size_bm, mat_size_bm*4);    
    // fprintf(fp, "each matrix takes %g Bytes\ntotal usage of matrices a,b,c and d is %g Bytes\n",mat_size_bm, mat_size_bm*4);
    
    // array of tests to be executed
    test_type tests[N_TESTS] = {
        &mat_mul,
        &mat_mul_function_calls,
        &mat_mul_function_calls2,
        &mat_mul_function_calls3,
        &mat_mul_function_calls4,
        &mat_mul_loop_unroll,
        &mat_mul_loop_unroll2,
        &mat_mul_loop_unroll3,
        &mat_mul_arr_priv,
        &mat_mul_arr_priv2,
        &mat_mul_pointer_alias,
        &mat_mul_pointer_alias2
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
        "mat_mul_arr_priv",
        "mat_mul_arr_priv2",
        "mat_mul_pointer_alias",
        "mat_mul_pointer_alias2"
    };

    double start, end;
    int i,j,k;    
    
    int** a = make_rand_mat(n,2);
    int** b = make_rand_mat(n,2);  
    int** c = make_zero_mat(n);
    int** d = make_zero_mat(n);
    
    printf("\ncomputing d = a*b with a serial calculation\n");    
    // fprintf(fp, "\ncomputing d = a*b with a serial calculating\n");
    start = omp_get_wtime();
    mat_mul_serial(n, a, b, d);
    end = omp_get_wtime();
    printf("finished computing d, in %lf seconds\n", end - start);    
    // fprintf(fp, "finished computing d, in %lf seconds\n", end - start);

    if(test_num > -1) {
        run_test(tests[test_num], test_names[test_num],n , a, b, c, d);
        printf("finished test\n",N_TESTS);     
    }
    else {
       // run all tests with a,b,c and n
        for(test_num = 0; test_num < N_TESTS; test_num++) {
            run_test(tests[test_num], test_names[test_num],n , a, b, c, d);
            // printf("\ncomputing c = a*b with test: %s\n",test_names[test_num]);        
            // // fprintf(fp, "\ncomputing c = a*b with test: %s\n",test_names[test_num]);
            // start = omp_get_wtime();
            // tests[test_num](n, a, b, c);
            // end = omp_get_wtime();
            // printf("finished test: %s, in %lf seconds\n", test_names[test_num], end - start);
            // // fprintf(fp, "finished test: %s, in %lf seconds\n", test_names[test_num], end - start);
            // printf("verifying that c == d\n");        
            // // fprintf(fp, "verifying that c == d\n");
            // if (compare_pat(n, &i, &j, c, d)) {
            //     printf("BAD RSULTS in test: %s!, c[%d][%d]: %d, d[%d][%d]: %d\n",test_names[test_num],i,j,c[i][j],i,j,d[i][j]);  
            // }
        }
        printf("finished %d tests\n",N_TESTS);    
    }

    


        
    // fprintf(fp, "finished %d tests\n",N_TESTS);
    // fclose(fp);

    free_mat(n, a);
    free_mat(n, b);
    free_mat(n, c);
    free_mat(n, d);
    
    return 0;

}
    