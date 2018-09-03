void p4a_kernel_mat_mul_function_calls2(int i, int j, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int k;
   if (i<=n-1&&j<=n-1) {
      c[i][j] = 0;
      for(k = 0; k <= n-1; k += 1)
         compute_cijk2(i, j, k, a, b, c);
   }
   ;
}
