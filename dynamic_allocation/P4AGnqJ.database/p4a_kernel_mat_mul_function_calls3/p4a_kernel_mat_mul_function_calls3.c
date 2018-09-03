void p4a_kernel_mat_mul_function_calls3(int i, int j, int **a, int **b, int **c, int n)
{
   if (i<=n-1&&j<=n-1)
      compute_cij(i, j, n, a, b, c);
   ;
}
