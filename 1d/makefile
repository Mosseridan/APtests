SIZE = 1000
SIZE_DEP = do_size size.h
P4A_OUT = mat_mul_p4a_$(SIZE).c
P4A_CUDA_OUT = mat_mul_p4a_cuda_$(SIZE).c
SIMD_OUT = mat_mul_simd_$(SIZE).c
C_FILES = run_tests.c utils.c
INCLUDE = -I.
FLAGS = -g -O3 -qopenmp -o
MIC_FLAGS= -mmic
CC = icc
OUT_DIR = bin

all: ser ser_xphi p4a p4a_xphi


ser: $(C_FILES) $(SIZE_DEP) mat_mul.c mk_out_dir
	test -d $(OUT_DIR)/xeon || mkdir $(OUT_DIR)/xeon
	test -d $(OUT_DIR)/xeon/ser || mkdir $(OUT_DIR)/xeon/ser
	$(CC) $(FLAGS) $(OUT_DIR)/xeon/ser/mm$(SIZE)-ser.out $(C_FILES) mat_mul.c $(INCLUDE)

ser_xphi: $(C_FILES) $(SIZE_DEP) mat_mul.c mk_out_dir
	test -d $(OUT_DIR)/xphi || mkdir $(OUT_DIR)/xphi
	test -d $(OUT_DIR)/xphi/ser || mkdir $(OUT_DIR)/xphi/ser
	$(CC) $(MIC_FLAGS) $(FLAGS) $(OUT_DIR)/xphi/ser/mm$(SIZE)-ser-xphi.out $(C_FILES) mat_mul.c $(INCLUDE)

p4a: $(C_FILES) do_p4a $(P4A_OUT) mk_out_dir
	test -d $(OUT_DIR)/xeon || mkdir $(OUT_DIR)/xeon
	test -d $(OUT_DIR)/xeon/p4a || mkdir $(OUT_DIR)/xeon/p4a
	$(CC) $(FLAGS) $(OUT_DIR)/xeon/p4a/mm$(SIZE)-p4a.out $(C_FILES) $(P4A_OUT) $(INCLUDE)

p4a_xphi: $(C_FILES) do_p4a $(P4A_OUT) mk_out_dir
	test -d $(OUT_DIR)/xphi || mkdir $(OUT_DIR)/xphi
	test -d $(OUT_DIR)/xphi/p4a || mkdir $(OUT_DIR)/xphi/p4a
	$(CC) $(MIC_FLAGS) $(FLAGS) $(OUT_DIR)/xphi/p4a/mm$(SIZE)-p4a-xphi.out $(C_FILES) $(P4A_OUT) $(INCLUDE)


simd_xphi: $(C_FILES) do_p4a $(P4A_OUT) mk_out_dir
	test -d $(OUT_DIR)/xphi || mkdir $(OUT_DIR)/xphi
	test -d $(OUT_DIR)/xphi/simd || mkdir $(OUT_DIR)/xphi/simd
	$(CC) $(MIC_FLAGS) $(FLAGS) $(OUT_DIR)/xphi/simd/mm$(SIZE)-simd-xphi.out $(C_FILES) $(P4A_OUT) $(INCLUDE)



mk_out_dir:
	test -d $(OUT_DIR) || mkdir $(OUT_DIR)

#test -d $(OUT_DIR)/$(PLATFORM) || mkdir $(OUT_DIR)/$(PLATFORM)
#test -d $(OUT_DIR)/$(PLATFORM)/$(PAR) || mkdir $(OUT_DIR)/$(PLATFORM)/$(PAR)


do_p4a: $(SIZE_DEP)
	test -f $(P4A_OUT) || p4a -O mat_mul.c -I. -vvv
	if test -f mat_mul.p4a.c; then mv mat_mul.p4a.c $(P4A_OUT); fi;

do_p4a_cuda: $(SIZE_DEP)
	test -f $(P4A_CUDA_OUT) || p4a -C mat_mul.c -I. -vvv
	if test -f mat_mul.p4a.cu; then mv mat_mul.p4a.cu $(P4A_CUDA_OUT); fi;


do_size:
	echo '#define N $(SIZE)' > size.h

clean:
	rm -rf *.o *.out  *_p4a_* P4A*
