#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "utils.h"

void print_mat(int n , int mat[N][N]) {
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


void make_rand_mat(int n, int mat[N][N], int max_val) {
    double begin,end;
    int i,j;

    begin = omp_get_wtime();  
    srand(time(NULL)); // generate rand seed from current time
    #pragma omp parallel for private(i,j) firstprivate (n)
    for (i = 0; i < n; i++) {
        #pragma omp parallel for private(j)
        for (j = 0; j < n; j++) {
            mat[i][j] = rand() % max_val;
        }
    }
    end = omp_get_wtime();
    printf("matrix initialization with random numbers took %lf seconds\n", end - begin);  
}


void make_zero_mat(int n, int mat[N][N]) {
    double begin,end;
    int i,j;

    begin = omp_get_wtime();  
    srand(time(NULL)); // generate rand seed from current time
    #pragma omp parallel for private(i,j) firstprivate (n)
    for (i = 0; i < n; i++) {
        #pragma omp parallel for private(j)
        for (j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }
    end = omp_get_wtime();
    printf("matrix initialization with zeros took %lf seconds\n", end - begin);  
}


int compare_pat(int n, int* bad_i, int* bad_j, int mat1[N][N], int mat2[N][N]) {
    int i,j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(mat1[i][j] - mat2[i][j]) {
                *bad_i = i;
                *bad_j = j;
                return 1;
            }
        }
    }
    return 0;
}


