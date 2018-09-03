void p4a_kernel_mat_mul_loop_unroll(int i, int j, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int k;
   if (i<=n-1&&j<=n-1) {
      c[i][j] = 0;
      for(k = 0; k <= n/2+(-1); k += 1)
         // we asume that n is even
         c[i][j] += a[i][2*k]*b[2*k][j]+a[i][2*k+1]*b[2*k+1][j];
   }
   ;
}
