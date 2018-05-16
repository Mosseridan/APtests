#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <utils.h>
#include <mat_mul.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

#define N_TESTS 12
#define STR_SIZE 100
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


void run_test(test_type test, const char* test_name, int n, int** a, int** b, int** c, int** d, FILE* log_file, double mat_size_mb) {
    int i,j;
    double start, end;
    printf("\ncomputing c = a*b with test: %s\n",test_name);        
    start = omp_get_wtime();
    test(n, a, b, c);
    end = omp_get_wtime();
    printf("finished test: %s, in %lf seconds\n", test_name, end - start);
    printf("verifying that c == d\n"); 
    if (compare_pat(n, &i, &j, c, d)) {
        printf("BAD RSULTS in test: %s!, c[%d][%d]: %d, d[%d][%d]: %d\n",test_name,i,j,c[i][j],i,j,d[i][j]);
        fprintf(log_file, "\n%d,%s,%lf,X,%lf", n, test_name, end - start, mat_size_mb);             
    }
    else {
        fprintf(log_file, "\n%d,%s,%lf,V,%lf", n, test_name, end - start, mat_size_mb);           
    }
}


int main(int argc, char** argv) {

    char *p;
    long n = 1000;
    long test_num = -1;
    errno = 0;
    
    double start, end;
    int i,j,k;    
    int** a; 
    int** b; 
    int** c;
    int** d;

    FILE* log_file;
    char filename[STR_SIZE];
    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);
    strftime(filename, sizeof(filename), "test_log_%Y%m%d%H%M%S.csv", timenow);
    
    for(i = 1; i < argc-1; i++) {
        if(strcmp(argv[i],"-n") == 0) {
            long conv = strtol(argv[i+1], &p, 10);
            if (errno == 0 && *p == '\0' && conv <= INT_MAX) {
                n = conv;
            }
            i++;
        }
        else if(strcmp(argv[i],"-t") == 0) {
            long conv = strtol(argv[i+1], &p, 10);
            if (errno == 0 && *p == '\0' && conv <= INT_MAX) {
                test_num = conv;
            }
            i++;
        }
        else if(strcmp(argv[i],"-j") == 0) {
            snprintf(filename, sizeof(filename),"%s.csv",argv[i+1]);
            i++;
        }
    }
    
    printf("using %s to log test results\n",filename);
    log_file = fopen(filename,"w");    
    fprintf(log_file, "n,test_name,time,correct,mat_size");
    
    printf("n is set to %d\n",n);    
    double mat_size_mb = ((double)n*(double)n*sizeof(int)+(double)n*sizeof(int*))/(double)1000000;
    printf("each matrix takes %g MB\ntotal usage of matrices a,b,c and d is %lf MB\n",mat_size_mb, mat_size_mb*4);    
    
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

    a = make_rand_mat(n,2);
    b = make_rand_mat(n,2);  
    c = make_zero_mat(n);
    d = make_zero_mat(n);
    
    printf("\ncomputing d = a*b with a serial calculation\n");    
    start = omp_get_wtime();
    mat_mul_serial(n, a, b, d);
    end = omp_get_wtime();
    printf("finished computing d, in %lf seconds\n", end - start);
    fprintf(log_file, "\n%d,%s,%lf,V,%lf", n, "mat_mul_serial", end - start,mat_size_mb, mat_size_mb);             
      

    if(test_num > -1) {
        run_test(tests[test_num], test_names[test_num],n , a, b, c, d, log_file, mat_size_mb);
        printf("finished test\n",N_TESTS);     
    }
    else {
       // run all tests with a,b,c and n
        for(test_num = 0; test_num < N_TESTS; test_num++) {
            run_test(tests[test_num], test_names[test_num],n , a, b, c, d, log_file, mat_size_mb);
        }
        printf("finished %d tests\n",N_TESTS);    
    }

    fclose(log_file);
    free_mat(n, a);
    free_mat(n, b);
    free_mat(n, c);
    free_mat(n, d);
    
    return 0;

}
    