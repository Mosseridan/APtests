# 4757
void mat_mul_arr_priv2(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    int* d = malloc(sizeof(int)*n); 
    for (i = 0;  i < n;  i++) { 
        for (j = 0;  j < n;  j++) { 
            d[i] = 0; 
            for (k = 0;  k < n;  k++) { 
                d[i] += a[i][k] * b[k][j]; 
            } 
            c[i][j] = d[i]; 
        } 
    } 
    return; 
}
