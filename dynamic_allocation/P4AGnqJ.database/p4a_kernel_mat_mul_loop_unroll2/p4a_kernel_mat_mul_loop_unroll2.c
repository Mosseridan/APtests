void p4a_kernel_mat_mul_loop_unroll2(int i, int j, int **a, int **b, int **c, int n)
{
   // Declared by Pass Outlining
   int k;
   // we asume that n is even
   c[i][2*j] = 0;
   for(k = 0; k <= n/2+(-1); k += 1)
      c[i][2*j] += a[i][2*k]*b[2*k][2*j]+a[i][2*k+1]*b[2*k+1][2*j];
   c[i][2*j+1] = 0;
   for(k = 0; k <= n/2+(-1); k += 1)
      c[i][2*j+1] += a[i][2*k]*b[2*k][2*j+1]+a[i][2*k+1]*b[2*k+1][2*j+1];
   ;
}
