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
   for(i = 0; i <= 4999; i += 1)
      for(j = 0; j <= 4999; j += 1) {
         c[i*5000+j] = 0;
         for(k = 0; k <= 4999; k += 1)
            for(t = 0; t <= 99; t += 1)
               c[i*5000+j] += a[i*5000+k]*b[j*5000+k];
      }
   return;
}
