void p4a_launcher_mat_mul_pointer_alias2(int **d, int **c, int n)
{
   // Declared by Pass Outlining
   int i, j;
   // Loop nest P4A begin,1D(n)
   for(i = 0; i <= n-1; i += 1)
      // Loop nest P4A end
      if (i<=n-1) {
         c[i][0] = 0;
         for(j = 1; j <= n-1; j += 1)
            c[i][j] = d[i][j-1];
      }
   ;
}
