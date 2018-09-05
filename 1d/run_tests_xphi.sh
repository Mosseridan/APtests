#!/bin/bash
#SBATCH -p xphi
#SBATCH -N 1
#SBATCH --exclusive

source /opt/sw/intel/parallel_studio_xe_2017/psxevars.sh mic
export SINK_LD_LIBRARY_PATH=/opt/sw/intel/compilers_and_libraries/linux/lib/mic
#micnativeloadex run_tests.out -d 0 -a "-n $SIZE" &> serial_$SIZE


#micnativeloadex	bin/xphi/p4a/mm1000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm1000_p4a_xphi.res 
#micnativeloadex bin/xphi/p4a/mm2000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm2000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm3000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm3000_p4a_xphi.res
#micnativeloadex	bin/xphi/p4a/mm4000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm4000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm5000_p4a_xphi.out -d 0 &> results/xphi/p4a/mm5000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm6000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm6000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm7000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm7000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm8000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm8000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm9000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm9000_p4a_xphi.res
#micnativeloadex bin/xphi/p4a/mm10000_p4a_xphi.out -d 1 &> results/xphi/p4a/mm10000_p4a_xphi.res


if test $1; then MAX_SIZE=$1; else MAX_SIZE=1000; fi
if test $2; then PAR=$2; else PAR=p4a; fi
if test $3; then SIZE=$3; else SIZE=1000; fi
test -d results || mkdir results
test -d results/xphi || mkdir results/xphi
test -d results/xphi/$PAR || mkdir results/xphi/$PAR


MIC_NUM=0
while [ $SIZE -le $MAX_SIZE ]
do
echo
echo
echo @@@@@@@@ $SIZE @@@@@@@@
echo Binary file: bin/xphi/$PAR/mm$SIZE-$PAR-xphi.out
echo Output file: results/xphi/$PAR/mm$SIZE-$PAR-xphi.res
echo Running on mic $MIC_NUM
micnativeloadex bin/xphi/$PAR/mm$SIZE-$PAR-xphi.out -d $MIC_NUM &> results/xphi/$PAR/mm$SIZE-$PAR-xphi.res
if test $MIC_NUM = 0; then 
	MIC_NUM=1
else 
	MIC_NUM=0
fi
((SIZE+=1000))
done
echo All done

