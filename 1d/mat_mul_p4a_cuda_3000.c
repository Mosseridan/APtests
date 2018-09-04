/* Use the Par4All accelerator run time: */
#include <p4a_accel.h>
/*
 * file for mat_mul.c
 */
#include "./mat_mul.h"
#include "./size.h"

void mat_mul(int *a, int *b, int *c);
//PIPS generated variable
void p4a_launcher_mat_mul(int *a, int *b, int *c);
//PIPS generated variable
P4A_accel_kernel p4a_kernel_mat_mul(int i, int j, int *a, int *b, int *c);
//PIPS generated variable
;
//PIPS generated variable
P4A_accel_kernel_wrapper p4a_wrapper_mat_mul(int i, int j, int *a, int *b, int *c);
//PIPS generated variable
;
//PIPS generated variable
;
//PIPS generated variable
void P4A_accel_malloc(void **address, size_t size);
//PIPS generated variable
void P4A_copy_to_accel_1d(size_t element_size, size_t d1_size, size_t d1_block_size, size_t d1_offset, const void *host_address, void *accel_address);
//PIPS generated variable
void P4A_copy_from_accel_1d(size_t element_size, size_t d1_size, size_t d1_block_size, size_t d1_offset, void *host_address, const void *accel_address);
//PIPS generated variable
void P4A_accel_free(void *address);
P4A_accel_kernel_wrapper p4a_wrapper_mat_mul(int i, int j, int *a, int *b, int *c)
{
   // Index has been replaced by P4A_vp_1:
   i = P4A_vp_1;
   // Index has been replaced by P4A_vp_0:
   j = P4A_vp_0;
   p4a_kernel_mat_mul(i, j, a, b, c);
}
P4A_accel_kernel p4a_kernel_mat_mul(int i, int j, int *a, int *b, int *c)
{
   // Declared by Pass Outlining
   int k;
   if (i<=2999&&j<=2999) {
      c[i*3000+j] = 0;
      for(k = 0; k <= 2999; k += 1)
         c[i*3000+j] += a[i*3000+k]*b[j*3000+k];
   }
}
void p4a_launcher_mat_mul(int *a, int *b, int *c)
{
   // Declared by Pass Outlining
   int i, j;
   P4A_call_accel_kernel_2d(p4a_wrapper_mat_mul, 3000, 3000, i, j, a, b, c);
}
void mat_mul(int *a, int *b, int *c)
{
   {
      //PIPS generated variable
      int (*p4a_var_c0)[9000000] = (int (*)[9000000]) 0, (*p4a_var_b0)[9000000] = (int (*)[9000000]) 0, (*p4a_var_a0)[9000000] = (int (*)[9000000]) 0;
      P4A_accel_malloc((void **) &p4a_var_a0, sizeof(int)*9000000);
      P4A_accel_malloc((void **) &p4a_var_b0, sizeof(int)*9000000);
      P4A_accel_malloc((void **) &p4a_var_c0, sizeof(int)*9000000);
      P4A_copy_to_accel_1d(sizeof(int), 9000000, 9000000, 0, &a[0], *p4a_var_a0);
      P4A_copy_to_accel_1d(sizeof(int), 9000000, 9000000, 0, &b[0], *p4a_var_b0);
      P4A_copy_to_accel_1d(sizeof(int), 9000000, 9000000, 0, &c[0], *p4a_var_c0);

      p4a_launcher_mat_mul(*p4a_var_a0, *p4a_var_b0, *p4a_var_c0);
      P4A_copy_from_accel_1d(sizeof(int), 9000000, 9000000, 0, &c[0], *p4a_var_c0);
      P4A_accel_free(p4a_var_a0);
      P4A_accel_free(p4a_var_b0);
      P4A_accel_free(p4a_var_c0);
   }
   return;
}
