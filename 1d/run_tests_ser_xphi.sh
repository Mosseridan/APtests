#!/bin/bash
#SBATCH -p xphi
#SBATCH -N 1
#SBATCH --exclusive

source /opt/sw/intel/parallel_studio_xe_2017/psxevars.sh
export SINK_LD_LIBRARY_PATH=/opt/sw/intel/compilers_and_libraries/linux/lib/mic
#micnativeloadex run_tests.out -d 0 -a "-n $SIZE" &> serial_$SIZE

test -d results || mkdir results
test -d results/xphi || mkdir results/xphi
test -d results/xphi/ser || mkdir results/xphi/ser

micnativeloadex	bin/xphi/ser/mm1000_ser_xphi.out -d 0 &> results/xphi/ser/mm1000_ser_xphi.res 
micnativeloadex bin/xphi/ser/mm2000_ser_xphi.out -d 1 &> results/xphi/ser/mm2000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm3000_ser_xphi.out -d 0 &> results/xphi/ser/mm3000_ser_xphi.res
micnativeloadex	bin/xphi/ser/mm4000_ser_xphi.out -d 1 &> results/xphi/ser/mm4000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm5000_ser_xphi.out -d 0 &> results/xphi/ser/mm5000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm6000_ser_xphi.out -d 1 &> results/xphi/ser/mm6000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm7000_ser_xphi.out -d 1 &> results/xphi/ser/mm7000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm8000_ser_xphi.out -d 1 &> results/xphi/ser/mm8000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm9000_ser_xphi.out -d 1 &> results/xphi/ser/mm9000_ser_xphi.res
micnativeloadex bin/xphi/ser/mm10000_ser_xphi.out -d 1 &> results/xphi/ser/mm10000_ser_xphi.res
