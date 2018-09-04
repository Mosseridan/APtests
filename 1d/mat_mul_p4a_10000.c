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
   for(i = 0; i <= 9999; i += 1)
      for(j = 0; j <= 9999; j += 1) {
         c[i*10000+j] = 0;
         for(k = 0; k <= 9999; k += 1)
            c[i*10000+j] += a[i*10000+k]*b[j*10000+k];
      }
   return;
}
