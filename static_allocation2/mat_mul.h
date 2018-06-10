#define N 1000

int[N][N] a;
int[N][N] b;
int[N][N] c;
int[N][N] d;

int compute_cijk(int i, int j, int k);

void compute_cijk2(int i, int j, int k);

void compute_cij(int i, int j , int n);

void compute_ci(int i, int n);

void mat_mul(int n);

void mat_mul_function_calls(int n);

void mat_mul_function_calls2(int n);

void mat_mul_function_calls3(int n);

void mat_mul_function_calls4(int n);

void mat_mul_loop_unroll(int n);

void mat_mul_loop_unroll2(int n);

void mat_mul_loop_unroll3(int n);

void mat_mul_arr_priv(int n);

void mat_mul_arr_priv2(int n);

void mat_mul_pointer_alias(int n);

void mat_mul_pointer_alias2(int n);