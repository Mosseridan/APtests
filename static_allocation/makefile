all: run_tests run_tests_p4a run_tests_cetus run_tests_rose 

run_tests: run_tests.c mat_mul.c utils.c
	gcc -g -fopenmp -o run_tests.out run_tests.c mat_mul.c utils.c -I.

run_tests_p4a: run_tests.c mat_mul_p4a.c utils.c
	gcc -g -fopenmp -o run_tests_p4a.out run_tests.c mat_mul_p4a.c utils.c -I.

run_tests_rose: run_tests.c mat_mul_rose.c utils.c
	gcc -g -fopenmp -o run_tests_rose.out run_tests.c mat_mul_rose.c utils.c -I.

run_tests_cetus: run_tests.c mat_mul_cetus.c utils.c
	gcc -g -fopenmp -o run_tests_cetus.out run_tests.c mat_mul_cetus.c utils.c -I.

mat_mul_p4a.c: mat_mul.c
	p4a -O mat_mul.c -I.
	mv mat_mul.p4a.c mat_mul_p4a.c

mat_mul_for_cetus.c: mat_mul.c
	cp mat_mul.c mat_mul_for_cetus.c
	sed -i '/^void.*alias(/,/^\}/d' mat_mul_for_cetus.c

mat_mul_cetus.c: mat_mul_for_cetus.c
	cetus -parallelize-loops=4 -alias=3 -expand-user-header mat_mul_for_cetus.c
	rm mat_mul_for_cetus.c
	mv cetus_output/mat_mul_for_cetus.c ./mat_mul_cetus.c
	rm -rf cetus_output

clean:
	rm -rf *.o *.out
	rm -rf *p4a* *cetus* *rose*
