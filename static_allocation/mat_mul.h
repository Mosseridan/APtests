#include "params.h"

int compute_cijk(int i, int j, int k, int a[N][N], int b[N][N]);

void compute_cijk2(int i, int j, int k, int a[N][N], int b[N][N], int c[N][N]);

void compute_cij(int i, int j , int n, int a[N][N], int b[N][N], int c[N][N]);

void compute_ci(int i, int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_function_calls(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_function_calls2(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_function_calls3(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_function_calls4(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_loop_unroll(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_loop_unroll2(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_loop_unroll3(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_arr_priv(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_arr_priv2(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_pointer_alias(int n, int a[N][N], int b[N][N], int c[N][N]);

void mat_mul_pointer_alias2(int n, int a[N][N], int b[N][N], int c[N][N]);