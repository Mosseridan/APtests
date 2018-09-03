# 4623
void compute_cijk2(int i, int j, int k, int** a, int** b, int** c) { 
     c[i][j] += a[i][k] * b[k][j]; 
}
