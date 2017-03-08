#!/bin/bash
QUEUE=medium
Time=48:00
Ndim=4
SIDE=64
#Main runs
Start=$1;
echo $Start;
    bsub -q $QUEUE -W $Time -W $Time "./bin/ising $Ndim $SIDE $Start";
