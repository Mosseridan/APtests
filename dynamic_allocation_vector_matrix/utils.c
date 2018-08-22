#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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

void free_vec(int n, int* mat) {
    free(mat);
}


int** make_rand_mat(int n, int max_val) {
    double begin,end;
    int i,j;
    int** mat = malloc(sizeof(int*)*n);

    begin = omp_get_wtime();  
    srand(time(NULL)); // generate rand seed from current time
    #pragma omp parallel for private(i,j) firstprivate (n)
    for (i = 0; i < n; i++) {
        mat[i] = malloc(sizeof(int)*n);
         #pragma omp parallel for private(j)
        for (j = 0; j < n; j++) {
            mat[i][j] = rand() % max_val;
        }
    }
    end = omp_get_wtime();
    printf("matrix initialization with random numbers took %lf seconds\n", end - begin);  
    return mat;
}


int** make_zero_mat(int n) {
    double begin,end;
    int i,j;
    int** mat = malloc (sizeof(int*)*n);

    begin = omp_get_wtime();  
    srand(time(NULL)); // generate rand seed from current time
    #pragma omp parallel for private(i,j) firstprivate (n)
    for (i = 0; i < n; i++) {
        mat[i] = calloc(n, sizeof(int));
    }
    end = omp_get_wtime();
    printf("matrix initialization with zeros took %lf seconds\n", end - begin);  
    return mat;
}


int compare_pat(int n, int* bad_i, int* mat1, int* mat2) {
    int i,j;
    for(i = 0; i < n; i++) {
            if(mat1[i] - mat2[i]) {
                *bad_i = i;
                return 1;
            }
    }
    return 0;
}


int* make_rand_vect(int n, int max_val) {
    int i;
    int * arr = (int*)malloc(sizeof(int)*n);
    if (max_val == 0) {
          for(i = 0; i < n; i++) {
            arr[i] = 0;
          }
    } else {
        srand(time(NULL));
        for(i = 0; i < n; i++) {
            arr[i] = rand() % max_val;
        }
    }
    return arr;
}