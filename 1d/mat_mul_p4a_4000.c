/*
 * file for mat_mul.c
 */
#include "./mat_mul.h"
#include "./size.h"

void mat_mul(int *a, int *b, int *c);
void mat_mul(int *a, int *b, int *c)
{
   int i, j, k, t;
#pragma omp parallel for private(j, t, k)
   for(i = 0; i <= 3999; i += 1)
      for(j = 0; j <= 3999; j += 1) {
         c[i*4000+j] = 0;
         for(k = 0; k <= 3999; k += 1)
            for(t = 0; t <= 99; t += 1)
               c[i*4000+j] += a[i*4000+k]*b[j*4000+k];
      }
   return;
}
