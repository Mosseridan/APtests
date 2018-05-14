#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <mat_mul_dyn.h>
#include <string.h>

#define N_TESTS 12
#define EPS 0

typedef void (*test_type)(int n,int** a ,int** b,int** c);

void print_mat(int n , int** mat) {
    int i,j;
    for (i = 0; i < n; i++){
        printf("%X: ",mat[i]);
        for (j = 0; j < n; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



void free_mat(int n, int** mat) {
    int i;
    for(i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

int** make_rand_mat(int n, int max_val) {
    int i,j;
    int** mat = malloc(sizeof(int*)*n);
    srand(time(NULL)); // generate rand seed from current time
    
    for (i = 0; i < n; i++) {
        mat[i] = malloc(sizeof(int)*n);
        for (j = 0; j < n; j++) {
            mat[i][j] = rand() % max_val;
        }
    }

    return mat;
}

int** make_zero_mat(int n) {
    int i,j;
    int** mat = malloc (sizeof(int*)*n);
    srand(time(NULL)); // generate rand seed from current time
    for (i = 0; i < n; i++) {
        mat[i] = malloc(sizeof(int)*n);
        for (j = 0; j < n; j++) {
            mat[i][j] = 0;       
        }
    }
    return mat;
}


int main(int argc, char** argv) {

    char *p;
    long n = 1000;
    errno = 0;
    
    // FILE* fp;
    // char filename[40];
    // struct tm *timenow;

    // time_t now = time(NULL);
    // timenow = gmtime(&now);

    // strftime(filename, sizeof(filename), "test_log_%Y%m%d%H%M%S.csv", timenow);
    // printf("using %s to log test results\n",filename);

    // fopen(filename,"w");

    if (argc >= 2) {
        long conv = strtol(argv[1], &p, 10);
        // Check for errors: e.g., the string does not represent an integer
        // or the integer is larger than int
         if (errno == 0 && *p == '\0' && conv <= INT_MAX) {
            n = conv;
         }
    }

    printf("n is set to %d\n",n);
    
    double mat_size_bm = (double)n*(double)n*sizeof(int)+(double)n*sizeof(int*);
    printf("each matrix takes %g Bytes\ntotal usage of matrices a,b,c and d is %g Bytes\n",mat_size_bm, mat_size_bm*4);
    
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

    clock_t begin, end;
    double time_spent;
    int i,j,k;    
    int** a = make_rand_mat(n,2);
    int** b = make_rand_mat(n,2);  
    int** c = make_zero_mat(n);
    int** d = make_zero_mat(n);

    printf("\ncomputing d = a*b with a serial calculating\n");
    begin = clock();
    mat_mul(n, a, b, d);
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
        for(i = 0; i < n && !bad; i++) {
            for(j = 0; j < n && !bad; j++) {
                int err = abs(c[i][j] - d[i][j]);
                if(err > EPS){
                    printf("BAD RSULTS in test: %s! err: %d, c[%d][%d]: %d, d[%d][%d]: %d\n",test_names[k],err,i,j,c[i][j],i,j,d[i][j]);
                    bad = 1;
                }
            }
        }
    }
        
    free_mat(n, a);
    free_mat(n, b);
    free_mat(n, c);
    free_mat(n, d);
    
    return 0;

}
    