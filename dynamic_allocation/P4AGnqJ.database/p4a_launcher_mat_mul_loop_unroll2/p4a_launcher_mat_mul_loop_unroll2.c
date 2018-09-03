void p4a_launcher_mat_mul_loop_unroll2(int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int i, j, k;
   for(i = 0; i <= n-1; i += 1)
      for(j = 0; j <= n-1-1; j += 2) {
         // we asume that n is even
         c[i][j] = 0;
         for(k = 0; k <= n-1-1; k += 2)
            c[i][j] += a[i][k]*b[k][j]+a[i][k+1]*b[k+1][j];
         c[i][j+1] = 0;
         for(k = 0; k <= n-1-1; k += 2)
            c[i][j+1] += a[i][k]*b[k][j+1]+a[i][k+1]*b[k+1][j+1];
      }
   ;
}
