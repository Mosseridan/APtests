void p4a_launcher_mat_mul_arr_priv2(int *d, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int i, j, k;
   // Loop nest P4A begin,1D(n)
   for(i = 0; i <= n-1; i += 1)
      // Loop nest P4A end
      if (i<=n-1)
         for(j = 0; j <= n-1; j += 1) {
            d[i] = 0;
            for(k = 0; k <= n-1; k += 1)
               d[i] += a[i][k]*b[k][j];
            c[i][j] = d[i];
         }
   ;
}
