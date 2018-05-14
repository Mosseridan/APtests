all: run_tests run_tests_dyn run_tests_dyn_p4a run_tests_dyn_rose run_tests_dyn_cetus 
# mat_mul mat_mul_function_calls mat_mul_function_calls2 mat_mul_function_calls3 mat_mul_function_calls4 mat_mul_loop_unroll mat_mul_loop_unroll2 mat_mul_loop_unroll3


run_tests: run_tests.c mat_mul.c
	gcc -fopenmp -o run_tests.out run_tests.c mat_mul.c -I.

run_tests_dyn: run_tests_dyn.c mat_mul_dyn.c
	gcc -fopenmp -o run_tests_dyn.out run_tests_dyn.c mat_mul_dyn.c -I.

run_tests_dyn_p4a: run_tests_dyn.c mat_mul_dyn_p4a.c
	gcc -fopenmp -o run_tests_dyn_p4a.out run_tests_dyn.c mat_mul_dyn_p4a.c -I.

run_tests_dyn_rose: run_tests_dyn.c mat_mul_dyn_rose.c
	gcc -fopenmp -o run_tests_dyn_rose.out run_tests_dyn.c mat_mul_dyn_rose.c -I.

run_tests_dyn_cetus: run_tests_dyn.c mat_mul_dyn_cetus.c
	gcc -fopenmp -o run_tests_dyn_cetus.out run_tests_dyn.c mat_mul_dyn_cetus.c -I.

clean:
	rm -rf *.o *.out
