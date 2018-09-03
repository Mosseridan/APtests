void p4a_kernel_mat_mul_function_calls4(int i, int **a, int **b, int **c, int n)
{
   if (i<=n-1)
      compute_ci(i, n, a, b, c);
   ;
}
