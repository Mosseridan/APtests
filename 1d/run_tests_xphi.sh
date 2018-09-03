#!/bin/bash
#SBATCH -p xphi
#SBATCH -N 1
#SBATCH --exclusive

source /opt/sw/intel/parallel_studio_xe_2017/psxevars.sh
export SINK_LD_LIBRARY_PATH=/opt/sw/intel/compilers_and_libraries/linux/lib/mic
#micnativeloadex run_tests.out -d 0 -a "-n $SIZE" &> serial_$SIZE
micnativeloadex mm_xphi/mm1k_xphi.out -d 0 &> results/mm1k_xphi.res 
micnativeloadex mm_xphi/mm2k_xphi.out -d 1 &> results/mm2k_xphi.res
micnativeloadex mm_xphi/mm3k_xphi.out -d 0 &> results/mm3k_xphi.res
micnativeloadex	mm_xphi/mm4k_xphi.out -d 1 &> results/mm4k_xphi.res
micnativeloadex mm_xphi/mm5k_xphi.out -d 0 &> results/mm5k_xphi.res
micnativeloadex mm_xphi/mm6k_xphi.out -d 1 &> results/mm6k_xphi.res

