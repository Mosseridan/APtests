void p4a_launcher_mat_mul_function_calls3(int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int i, j;
   // Loop nest P4A begin,2D(n, n)
   for(i = 0; i <= n-1; i += 1)
      for(j = 0; j <= n-1; j += 1)
         // Loop nest P4A end
         if (i<=n-1&&j<=n-1)
            compute_cij(i, j, n, a, b, c);
   ;
}
