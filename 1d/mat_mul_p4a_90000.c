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
   for(i = 0; i <= 89999; i += 1)
      for(j = 0; j <= 89999; j += 1) {
         c[i*90000+j] = 0;
         for(k = 0; k <= 89999; k += 1)
            c[i*90000+j] += a[i*90000+k]*b[j*90000+k];
      }
   return;
}
