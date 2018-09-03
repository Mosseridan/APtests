void p4a_kernel_mat_mul_arr_priv2(int i, int **a, int **b, int **c, int *d, int n)
{
   // Declared by Pass Outlining
   int j, k;
   if (i<=n-1)
      for(j = 0; j <= n-1; j += 1) {
         d[i] = 0;
         for(k = 0; k <= n-1; k += 1)
            d[i] += a[i][k]*b[k][j];
         c[i][j] = d[i];
      }
   ;
}
