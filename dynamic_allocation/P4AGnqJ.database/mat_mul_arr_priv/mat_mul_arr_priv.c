# 4740
void mat_mul_arr_priv(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    int* d = malloc(sizeof(int)*n); 
    for (i = 0;  i < n;  i++) { 
        d[i] = 0; 
        for (j = 0;  j < n;  j++) { 
            d[i] = i; 
            c[d[i]][j] = 0; 
            for (k = 0;  k < n;  k++) { 
                c[i][j] += a[i][k] * b[k][j]; 
            } 
        } 
    } 
    return; 
}
