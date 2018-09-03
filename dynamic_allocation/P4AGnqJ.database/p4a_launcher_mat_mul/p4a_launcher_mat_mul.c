void p4a_launcher_mat_mul(int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int i, j, k;
   // Loop nest P4A begin,2D(n, n)
   for(i = 0; i <= n-1; i += 1)
      for(j = 0; j <= n-1; j += 1)
         // Loop nest P4A end
         if (i<=n-1&&j<=n-1) {
            c[i][j] = 0;
            for(k = 0; k <= n-1; k += 1)
               c[i][j] += a[i][k]*b[k][j];
         }
   ;
}
