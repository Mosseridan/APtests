void p4a_kernel_mat_mul_function_calls(int i, int j, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int k;
   if (i<=n-1&&j<=n-1) {
      c[i][j] = 0;
      for(k = 0; k <= n-1; k += 1)
         c[i][j] += compute_cijk(i, j, k, a, b);
   }
   ;
}
