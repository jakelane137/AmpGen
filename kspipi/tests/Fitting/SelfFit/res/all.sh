#!/bin/bash
for i in opts/*
do
    f=${i%.*}
    O=${f##*/}
    toyfit --opt $i --output output/$O --nEvents 10000
done
