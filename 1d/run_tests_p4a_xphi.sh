#!/bin/bash
#SBATCH -p xphi
#SBATCH -N 1
#SBATCH --exclusive

source /opt/sw/intel/parallel_studio_xe_2017/psxevars.sh
export SINK_LD_LIBRARY_PATH=/opt/sw/intel/compilers_and_libraries/linux/lib/mic
#micnativeloadex run_tests.out -d 0 -a "-n $SIZE" &> serial_$SIZE

test -d results || mkdir results
test -d results/xphi || mkdir results/xphi
test -d results/xphi/p4a || mkdir results/xphi/p4a

micnativeloadex	bin/xphi/p4a/mm1000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm1000_p4a_xphi.res 
micnativeloadex bin/xphi/p4a/mm2000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm2000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm3000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm3000_p4a_xphi.res
micnativeloadex	bin/xphi/p4a/mm4000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm4000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm5000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm5000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm6000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm6000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm7000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm7000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm8000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm8000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm9000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm9000_p4a_xphi.res
micnativeloadex bin/xphi/p4a/mm10000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm10000_p4a_xphi.res
