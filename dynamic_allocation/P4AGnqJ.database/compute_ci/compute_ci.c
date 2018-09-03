# 4666
void compute_ci(int i, int n, int** a, int** b, int** c) { 
    int j,k; 
    for (j = 0;  j < n;  j++) { 
        c[i][j] = 0; 
        for (k = 0;  k < n;  k++) { 
            c[i][j] += a[i][k] * b[k][j]; 
        } 
    } 
}
