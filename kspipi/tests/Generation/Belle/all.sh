#!/bin/bash
N=${1:-10000}
for i in opts/*.opt
do
   
    f=${i%.*}
    O=${f##*/}
    #echo $O
   diff.py --generate --output $O --input1 $f --input2 $f --nEvents $N $i $i
done
