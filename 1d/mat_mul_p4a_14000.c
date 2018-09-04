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
   for(i = 0; i <= 13999; i += 1)
      for(j = 0; j <= 13999; j += 1) {
         c[i*14000+j] = 0;
         for(k = 0; k <= 13999; k += 1)
            c[i*14000+j] += a[i*14000+k]*b[j*14000+k];
      }
   return;
}
