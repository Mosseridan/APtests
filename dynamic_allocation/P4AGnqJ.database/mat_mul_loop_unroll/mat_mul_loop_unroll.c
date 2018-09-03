# 4688
void mat_mul_loop_unroll(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    for (i = 0;  i < n;  i++) { 
        for (j = 0;  j < n;  j++) { 
            c[i][j] = 0; 
            for (k = 0;  k < n-1;  k += 2) {  // we asume that n is even
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]); 
            } 
        } 
    } 
    return; 
}
