#!/bin/bash
N=${1:-10000}
for i in *.opt
do
   
    O=${i%.*}
    #echo $O
    diff.py --generate --output $O --nEvents $N $O
done
