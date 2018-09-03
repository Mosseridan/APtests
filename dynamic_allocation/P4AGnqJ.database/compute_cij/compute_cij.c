# 4644
void compute_cij(int i, int j , int n, int** a, int** b, int** c) { 
    int k; 
    c[i][j] = 0; 
    for (k = 0;  k < n;  k++) { 
        c[i][j] += a[i][k] * b[k][j]; 
    } 
}
