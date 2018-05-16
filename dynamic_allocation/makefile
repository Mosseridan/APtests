all: run_tests run_tests run_tests_p4a run_tests_rose 
# run_tests_cetus 

run_tests: run_tests.c mat_mul.c utils.c
	gcc -g -fopenmp -o run_tests.out run_tests.c mat_mul.c utils.c -I.

run_tests_p4a: run_tests.c mat_mul_p4a.c utils.c
	gcc -g -fopenmp -o run_tests_p4a.out run_tests.c mat_mul_p4a.c utils.c -I.

run_tests_rose: run_tests.c mat_mul_rose.c utils.c
	gcc -g -fopenmp -o run_tests_rose.out run_tests.c mat_mul_rose.c utils.c -I.

run_tests_cetus: run_tests.c mat_mul_cetus.c utils.c
	gcc -g -fopenmp -o run_tests_cetus.out run_tests.c mat_mul_cetus.c utils.c -I.

clean:
	rm -rf *.o *.out
