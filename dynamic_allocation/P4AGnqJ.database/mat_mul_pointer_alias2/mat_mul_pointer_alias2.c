# 4787
void mat_mul_pointer_alias2(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    int** d = c; 
    for (i = 0;  i < n;  i++) { 
        c[i][0] = 0; 
        for (j = 1;  j < n;  j++) { 
            c[i][j] = d[i][j-1]; 
        } 
    } 
    for (i = 0;  i < n;  i++) { 
        for (j = 0;  j < n;  j++) { 
            for (k = 0;  k < n;  k++) { 
                c[i][j] += a[i][k] * b[k][j]; 
            } 
        } 
    } 
    return; 
}
