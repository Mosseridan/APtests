void p4a_launcher_mat_mul_function_calls4(int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int i;
   // Loop nest P4A begin,1D(n)
   for(i = 0; i <= n-1; i += 1)
      // Loop nest P4A end
      if (i<=n-1)
         compute_ci(i, n, a, b, c);
   ;
}
