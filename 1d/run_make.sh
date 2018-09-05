#!/bin/bash

if test $1; then TARGET=$1; else TARGET=ser; fi
if test $2; then MAX_SIZE=$2; else MAX_SIZE=1000; fi

SIZE=1000
while [ $SIZE -le $MAX_SIZE ]
do
echo
echo
echo @@@@@@@@ $SIZE @@@@@@@@
echo 
echo
make $TARGET SIZE=$SIZE
((SIZE+=1000))
done
echo All done

