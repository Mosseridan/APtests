# 4654
void mat_mul_function_calls3(int n, int** a, int** b, int** c) { 
    int i,j; 
    for (i = 0;  i < n;  i++) { 
        for (j = 0;  j < n;  j++) { 
            compute_cij(i,j,n,a,b,c); 
        } 
    } 
    return; 
}
