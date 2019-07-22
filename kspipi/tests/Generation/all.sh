#!/bin/bash
mkdir new_opts
for i in opts/*
do
    f=${i%.*}
    O=${f##*/}
    convertOpt --file $i --target new_opts/$O
#    ampplot --opt $i --output output/$O --nEvents 10000 --generate
done
for i in new_opts/*
do
    f=${i%.*}
    O=${f##*/}
#    convertOpt --file $i --target new_opts/$O
    ampplot --opt $i --output output/$O --nEvents 10000 --generate
done
