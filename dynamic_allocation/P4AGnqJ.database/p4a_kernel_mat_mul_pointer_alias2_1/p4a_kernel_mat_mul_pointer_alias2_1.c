void p4a_kernel_mat_mul_pointer_alias2_1(int i, int j, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int k;
   if (i<=n-1&&j<=n-1)
      for(k = 0; k <= n-1; k += 1)
         c[i][j] += a[i][k]*b[k][j];
   ;
}
