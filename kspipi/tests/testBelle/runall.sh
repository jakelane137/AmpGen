#!/bin/bash
N=${1:-10000}
for i in opts/*
do
   
    f=${i%.*}
    O=${f##*/}
    #echo $O
   diff.py --generate --output $O --nEvents $N $f $f
done
