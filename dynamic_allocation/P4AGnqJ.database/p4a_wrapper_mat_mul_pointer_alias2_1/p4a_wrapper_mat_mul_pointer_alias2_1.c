void p4a_wrapper_mat_mul_pointer_alias2_1(int i, int j, int **a, int **b, int **c, int n)
{
   // To be assigned to a call to P4A_vp_1: i
   // To be assigned to a call to P4A_vp_0: j
   p4a_kernel_mat_mul_pointer_alias2_1(i, j, a, b, c, n);
   ;
}
