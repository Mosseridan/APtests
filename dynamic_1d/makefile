all: run_tests run_tests run_tests_p4a run_tests_rose run_tests_cetus 

run_tests: run_tests.c mat_mul.c
	gcc -g -fopenmp -o run_tests.out run_tests.c mat_mul.c -I.

run_tests_p4a: run_tests.c mat_mul_p4a.c
	gcc -g -fopenmp -o run_tests_p4a.out run_tests.c mat_mul_p4a.c -I.

run_tests_rose: run_tests.c mat_mul_rose.c
	gcc -g -fopenmp -o run_tests_rose.out run_tests.c mat_mul_rose.c -I.

run_tests_cetus: run_tests.c mat_mul_cetus.c
	gcc -g -fopenmp -o run_tests_cetus.out run_tests.c mat_mul_cetus.c -I.

clean:
	rm -rf *.o *.out
