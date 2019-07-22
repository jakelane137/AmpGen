#!/bin/bash
n=${1:-10}
for i in opts/*.opt
do
	f=${i%.*}
	O=${f##*/}
	fitStats --model $i --output fitStats/$O --sampleSize $n
done
