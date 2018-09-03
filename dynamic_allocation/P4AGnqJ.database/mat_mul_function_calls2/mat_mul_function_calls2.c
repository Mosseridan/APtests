# 4629
void mat_mul_function_calls2(int n, int** a, int** b, int** c) { 
    int i,j,k; 
    for (i = 0;  i < n;  i++) { 
        for (j = 0;  j < n;  j++) { 
            c[i][j] = 0; 
            for (k = 0;  k < n;  k++) { 
                compute_cijk2(i,j,k,a,b,c); 
            } 
        } 
    } 
    return; 
}
