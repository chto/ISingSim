#!/bin/bash
QUEUE=medium
Time=48:00
Ndim=3
SIDE=48
#Main runs
Start=$1;
End=`echo $Start+0.1-0.01| bc -l`
for i in $(seq $Start 0.01 $End); do
    echo $i;
    bsub -q $QUEUE -W $Time -W $Time "./bin/ising $Ndim $SIDE $i";
done;
