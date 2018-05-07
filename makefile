all: run_tests 
# mat_mul mat_mul_function_calls mat_mul_function_calls2 mat_mul_function_calls3 mat_mul_function_calls4 mat_mul_loop_unroll mat_mul_loop_unroll2 mat_mul_loop_unroll3


run_tests: run_tests.c mat_mul.c
	gcc -o run_tests.out run_tests.c mat_mul.c -I.


# mat_mul: mat_mul.c
# 	gcc -o mat_mul.out mat_mul.c -I


# mat_mul_function_calls: mat_mul_function_calls.c
# 	gcc -o mat_mul_function_calls.out mat_mul_function_calls.c


# mat_mul_function_calls2: mat_mul_function_calls2.c
# 	gcc -o mat_mul_function_calls2.out mat_mul_function_calls2.c


# mat_mul_function_calls3: mat_mul_function_calls3.c
# 	gcc -o mat_mul_function_calls3.out mat_mul_function_calls3.c


# mat_mul_function_calls4: mat_mul_function_calls4.c
# 	gcc -o mat_mul_function_calls4.out mat_mul_function_calls4.c


# mat_mul_loop_unroll: mat_mul_loop_unroll.c
# 	gcc -o mat_mul_loop_unroll.out mat_mul_loop_unroll.c


# mat_mul_loop_unroll2: mat_mul_loop_unroll2.c
# 	gcc -o mat_mul_loop_unroll2.out mat_mul_loop_unroll2.c


# mat_mul_loop_unroll3: mat_mul_loop_unroll3.c
# 	gcc -o mat_mul_loop_unroll3.out mat_mul_loop_unroll3.c



clean:
	rm -rf *.o *.out
