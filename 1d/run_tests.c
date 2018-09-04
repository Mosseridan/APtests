#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <size.h>
#include <utils.h>
#include <mat_mul.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

#define N_TESTS 1
#define STR_SIZE 100
typedef void (*test_type)(int* a ,int* b,int* c);

void run_test(test_type test, const char* test_name, int* a, int* b, int* c, FILE* log_file, double mat_size_mb) {
    int i,j;
    double start, end;
    printf("\ncomputing c = a*b with test: %s\n",test_name);        
    start = omp_get_wtime();
    test(a, b, c);
    end = omp_get_wtime();
    printf("finished test: %s, in %lf seconds\n", test_name, end - start);
    fprintf(log_file, "\n%d,%s,%lf,V,%lf", N, test_name, end - start, mat_size_mb);
}


int main(int argc, char** argv) {

    char *p;
    long test_num = -1;
    errno = 0;
    
    double start, end;
    int i,j,k;    
    int* a; 
    int* b; 
    int* c;

    FILE* log_file;
    char filename[STR_SIZE];
    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);
    strftime(filename, sizeof(filename), "test_log_%Y%m%d%H%M%S.csv", timenow);
    
    for(i = 1; i < argc-1; i++) {
        if(strcmp(argv[i],"-j") == 0) {
            snprintf(filename, sizeof(filename),"%s.csv",argv[i+1]);
            i++;
        }
    }
    
    printf("using %s to log test results\n",filename);
    log_file = fopen(filename,"w");    
    fprintf(log_file, "n,test_name,time,correct,mat_size");
    
    printf("N is set to %d\n",N);    
    double mat_size_mb = ((double)N*(double)N*sizeof(int)+(double)N*sizeof(int*))/(double)1000000;
    printf("each matrix takes %g MB\ntotal usage of matrices a,b,c and d is %lf MB\n",mat_size_mb, mat_size_mb*4);    
    
    // array of tests to be executed
    test_type tests[N_TESTS] = {
        &mat_mul
    };

    const char* test_names[N_TESTS] = { 
        "mat_mul"
    };

    a = make_rand_mat_1d(N,2);
    b = make_rand_mat_1d(N,2);  
    c = make_zero_mat_1d(N);
    
    if(test_num > -1) {
        run_test(tests[test_num], test_names[test_num], a, b, c, log_file, mat_size_mb);
        printf("finished test %d\n",test_num);     
    }
    else {
       // run all tests with a,b,c and N
        for(test_num = 0; test_num < N_TESTS; test_num++) {
            run_test(tests[test_num], test_names[test_num] , a, b, c, log_file, mat_size_mb);
        }
        printf("finished %d tests\n",N_TESTS);    
    }

    fclose(log_file);
    free(a);
    free(b);
    free(c);
    
    return 0;

}
