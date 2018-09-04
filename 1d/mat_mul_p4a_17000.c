/*
 * file for mat_mul.c
 */
#include "./mat_mul.h"
#include "./size.h"

void mat_mul(int *a, int *b, int *c);
void mat_mul(int *a, int *b, int *c)
{
   int i, j, k;
#pragma omp parallel for private(j, k)
   for(i = 0; i <= 16999; i += 1)
      for(j = 0; j <= 16999; j += 1) {
         c[i*17000+j] = 0;
         for(k = 0; k <= 16999; k += 1)
            c[i*17000+j] += a[i*17000+k]*b[j*17000+k];
      }
   return;
}
