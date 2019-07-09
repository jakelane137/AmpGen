#!/bin/bash
for i in opts/*.opt
do
   
    f=${i%.*}
    O=${f##*/}
    #echo $O
   toyfit "$@" --opt $i --output $O
done
