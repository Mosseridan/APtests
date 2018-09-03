# 4720
void mat_mul_loop_unroll3(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    for (i = 0;  i < n-1;  i+=2) {  // we asume that n is even
        for (j = 0;  j < n-1;  j+= 2) { 
            c[i][j] = 0; 
            c[i][j+1] = 0; 
            c[i+1][j] = 0; 
            c[i+1][j+1] = 0; 
            for (k = 0;  k < n-1;  k += 2) { 
                c[i][j] += (a[i][k] * b[k][j] + a[i][k+1] * b[k+1][j]); 
                c[i][j+1] += (a[i][k] * b[k][j+1] + a[i][k+1] * b[k+1][j+1]); 
                c[i+1][j] += (a[i+1][k] * b[k][j] + a[i+1][k+1] * b[k+1][j]); 
                c[i+1][j+1] += (a[i+1][k] * b[k][j+1] + a[i+1][k+1] * b[k+1][j+1]); 
            } 
        } 
    } 
    return; 
}
