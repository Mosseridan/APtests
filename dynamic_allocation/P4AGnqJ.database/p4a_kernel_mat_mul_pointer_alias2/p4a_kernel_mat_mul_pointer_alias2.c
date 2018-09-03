void p4a_kernel_mat_mul_pointer_alias2(int i, int **c, int **d, int n)
{
   // Declared by Pass Outlining
   int j;
   if (i<=n-1) {
      c[i][0] = 0;
      for(j = 0; j <= n-2; j += 1)
         c[i][j+1] = d[i][j+1-1];
   }
   ;
}
