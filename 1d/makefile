all: normal xphi

normal: run_tests.c mat_mul.c utils.c
	icc -g -O3 -qopenmp -o mm.out run_tests.c mat_mul.c utils.c -I.

xphi: run_tests.c mat_mul.c utils.c
	icc -g -O3 -qopenmp -mmic -o mm_xphi.out run_tests.c mat_mul.c utils.c -I.

clean:
	rm -rf *.o *.out
